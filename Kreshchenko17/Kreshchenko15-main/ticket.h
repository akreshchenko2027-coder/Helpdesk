#pragma once
#include <QString>
#include <QDateTime>

struct Ticket
{
    int id;
    QString title;
    QString status;
    QString priority;
    QDateTime createdAt;
};
