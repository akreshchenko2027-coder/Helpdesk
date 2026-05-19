#ifndef PASSWORDREPOSITORY_H
#define PASSWORDREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include "PasswordRecord.h"

class PasswordRepository
{
public:
    PasswordRepository();
    ~PasswordRepository();

    QList<PasswordRecord> loadAll() const;
    bool insert(const PasswordRecord &item);
    bool update(const PasswordRecord &item);
    bool remove(int id);

private:
    QSqlDatabase m_db;
    void initDatabase();
};

#endif // PASSWORDREPOSITORY_H
