#include "PasswordLeakChecker.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QCryptographicHash>
#include <chrono>

PasswordLeakChecker::PasswordLeakChecker(QObject *parent)
    : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &PasswordLeakChecker::onReplyFinished);
}

void PasswordLeakChecker::checkPassword(const QString &password)
{
    if (password.isEmpty()) {
        emit checkFailed("Пароль порожній.");
        return;
    }

    // Хешуємо в SHA-1
    QByteArray sha1 = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex().toUpper();

    QByteArray prefix = sha1.left(5);
    m_currentSuffix = sha1.mid(5);

    QUrl url(QString("https://api.pwnedpasswords.com/range/%1").arg(QString(prefix)));
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent", "QtPasswordManager/1.0");
    request.setRawHeader("Add-Padding", "true");
    request.setTransferTimeout(std::chrono::seconds(5));

    m_networkManager.get(request);
}

void PasswordLeakChecker::onReplyFinished(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        emit checkFailed(QString("Помилка мережі: %1").arg(reply->errorString()));
        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        emit checkFailed(QString("Помилка сервера HTTP: %1").arg(statusCode));
        return;
    }

    QByteArray responseData = reply->readAll();
    QList<QByteArray> lines = responseData.split('\n');

    bool isLeaked = false;
    int leakCount = 0;

    for (const QByteArray &line : lines) {
        QByteArray cleanLine = line.trimmed();
        if (cleanLine.isEmpty()) continue;

        QList<QByteArray> parts = cleanLine.split(':');
        if (parts.size() == 2) {
            if (parts[0] == m_currentSuffix) {
                isLeaked = true;
                leakCount = parts[1].toInt();
                break;
            }
        }
    }

    emit checkCompleted(isLeaked, leakCount);
}
