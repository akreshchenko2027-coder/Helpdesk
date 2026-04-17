#pragma once

#include <QString>

struct VaultRecord
{
    int id = 0;
    QString title;
    QString username;
    QString password;
    QString website;
    QString category;
    QString updatedAt;
};
