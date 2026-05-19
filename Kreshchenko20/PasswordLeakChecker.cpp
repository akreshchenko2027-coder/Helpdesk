#include "PasswordLeakChecker.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QCryptographicHash>
#include <QEventLoop>

bool PasswordLeakChecker::checkPasswordSync(const QString &password, int &count) {
    QNetworkAccessManager manager;
    QByteArray sha1 = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex().toUpper();
    QByteArray prefix = sha1.left(5);
    QByteArray suffix = sha1.mid(5);

    QNetworkRequest request(QUrl("https://api.pwnedpasswords.com/range/" + QString(prefix)));
    request.setRawHeader("Add-Padding", "true");

    QEventLoop loop;
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool found = false;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        for (const QByteArray &line : data.split('\n')) {
            if (line.startsWith(suffix)) {
                count = line.split(':')[1].toInt();
                found = true;
                break;
            }
        }
    }
    reply->deleteLater();
    return found;
}
