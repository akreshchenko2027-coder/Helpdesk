#ifndef PASSWORDLEAKCHECKER_H
#define PASSWORDLEAKCHECKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop> // Для синхронного виклику у фоновому потоці

class PasswordLeakChecker : public QObject {
    Q_OBJECT
public:
    explicit PasswordLeakChecker(QObject *parent = nullptr);
    // Метод, який буде викликатися у фоновому потоці
    static bool checkPasswordSync(const QString &password, int &count);
};

#endif
