#ifndef REQUESTENTRY_H
#define REQUESTENTRY_H

#include <QString>
#include <QDateTime>

struct RequestEntry
{
    int id = 0;
    QString title;
    QString priority;
    QString status;
    QString description;
    QDateTime createdAt;
};

#endif
