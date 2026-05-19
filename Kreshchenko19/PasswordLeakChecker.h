#ifndef PASSWORDLEAKCHECKER_H
#define PASSWORDLEAKCHECKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class PasswordLeakChecker : public QObject
{
    Q_OBJECT
public:
    explicit PasswordLeakChecker(QObject *parent = nullptr);
    void checkPassword(const QString &password);

signals:
    void checkCompleted(bool found, int count);
    void checkFailed(const QString &message);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
    QByteArray m_currentSuffix;
};

#endif
