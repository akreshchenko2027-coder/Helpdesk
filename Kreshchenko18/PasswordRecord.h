#ifndef PASSWORDRECORD_H
#define PASSWORDRECORD_H

#include <QString>

struct PasswordRecord {
    int id = 0;
    QString title;
    QString login;
    QString secret;
    QString site;
    QString category;
    QString updatedAt;
};

#endif // PASSWORDRECORD_H
