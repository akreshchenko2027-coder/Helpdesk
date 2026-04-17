#include "vaultrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

VaultRepository::VaultRepository(const QSqlDatabase &db)
{
    m_db = db;
}

QList<VaultRecord> VaultRepository::loadAll() const
{
    QList<VaultRecord> list;

    QSqlQuery q(m_db);

    if (!q.exec("SELECT id,title,username,password,website,category,updated_at FROM vault_items"))
    {
        qDebug() << q.lastError().text();
        return list;
    }

    while (q.next())
    {
        VaultRecord r;
        r.id = q.value(0).toInt();
        r.title = q.value(1).toString();
        r.username = q.value(2).toString();
        r.password = q.value(3).toString();
        r.website = q.value(4).toString();
        r.category = q.value(5).toString();
        r.updatedAt = q.value(6).toString();

        list.append(r);
    }

    return list;
}

bool VaultRepository::insert(const VaultRecord &r)
{
    QSqlQuery q(m_db);

    q.prepare(
        "INSERT INTO vault_items "
        "(title,username,password,website,category,updated_at) "
        "VALUES (?,?,?,?,?,?)"
        );

    q.addBindValue(r.title);
    q.addBindValue(r.username);
    q.addBindValue(r.password);
    q.addBindValue(r.website);
    q.addBindValue(r.category);
    q.addBindValue(r.updatedAt);

    return q.exec();
}

bool VaultRepository::update(const VaultRecord &r)
{
    QSqlQuery q(m_db);

    q.prepare(
        "UPDATE vault_items SET "
        "title=?,username=?,password=?,website=?,category=?,updated_at=? "
        "WHERE id=?"
        );

    q.addBindValue(r.title);
    q.addBindValue(r.username);
    q.addBindValue(r.password);
    q.addBindValue(r.website);
    q.addBindValue(r.category);
    q.addBindValue(r.updatedAt);
    q.addBindValue(r.id);

    return q.exec();
}

bool VaultRepository::remove(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM vault_items WHERE id=?");
    q.addBindValue(id);

    return q.exec();
}
