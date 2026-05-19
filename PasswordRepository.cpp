#include "PasswordRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

PasswordRepository::PasswordRepository()
{
    initDatabase();
}

PasswordRepository::~PasswordRepository()
{
    if (m_db.isOpen()) m_db.close();
}

void PasswordRepository::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("passwords.db");

    if (m_db.open()) {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS credentials ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "title TEXT, login TEXT, secret TEXT, "
                   "site TEXT, category TEXT, updated_at TEXT)");
    }
}

QList<PasswordRecord> PasswordRepository::loadAll() const
{
    QList<PasswordRecord> list;
    QSqlQuery query("SELECT id, title, login, secret, site, category, updated_at FROM credentials");
    while (query.next()) {
        PasswordRecord r;
        r.id = query.value(0).toInt();
        r.title = query.value(1).toString();
        r.login = query.value(2).toString();
        r.secret = query.value(3).toString();
        r.site = query.value(4).toString();
        r.category = query.value(5).toString();
        r.updatedAt = query.value(6).toString();
        list.append(r);
    }
    return list;
}

bool PasswordRepository::insert(const PasswordRecord &item)
{
    QSqlQuery query;
    query.prepare("INSERT INTO credentials (title, login, secret, site, category, updated_at) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(item.title);
    query.addBindValue(item.login);
    query.addBindValue(item.secret);
    query.addBindValue(item.site);
    query.addBindValue(item.category);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    return query.exec();
}

bool PasswordRepository::update(const PasswordRecord &item)
{
    QSqlQuery query;
    query.prepare("UPDATE credentials SET title=?, login=?, secret=?, site=?, category=?, updated_at=? WHERE id=?");
    query.addBindValue(item.title);
    query.addBindValue(item.login);
    query.addBindValue(item.secret);
    query.addBindValue(item.site);
    query.addBindValue(item.category);
    query.addBindValue(item.updatedAt);
    query.addBindValue(item.id);
    return query.exec();
}

bool PasswordRepository::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM credentials WHERE id=?");
    query.addBindValue(id);
    return query.exec();
}
