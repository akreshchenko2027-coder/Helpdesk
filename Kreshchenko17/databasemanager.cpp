#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool DatabaseManager::open(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "DB open error:" << m_db.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::init()
{
    QSqlQuery query(m_db);

    return query.exec(
        "CREATE TABLE IF NOT EXISTS vault_items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT,"
        "username TEXT,"
        "password TEXT,"
        "website TEXT,"
        "category TEXT,"
        "updated_at TEXT"
        ")"
        );
}
