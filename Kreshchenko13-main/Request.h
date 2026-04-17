#pragma once
#include <QString>
#include <QDateTime>

struct Request
{
    int id = 0;
    QString subject;
    QString details;
    QString state;
    QString level;
    QDateTime createdAt;
};
