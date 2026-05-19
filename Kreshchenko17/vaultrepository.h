#pragma once

#include <QSqlDatabase>
#include <QList>
#include "vaultrecord.h"

class VaultRepository
{
public:
    VaultRepository(const QSqlDatabase &db);

    QList<VaultRecord> loadAll() const;

    bool insert(const VaultRecord &r);
    bool update(const VaultRecord &r);
    bool remove(int id);

private:
    QSqlDatabase m_db;
};
