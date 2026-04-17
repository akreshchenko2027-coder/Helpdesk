#pragma once

#include <QSqlDatabase>

class DatabaseManager
{
public:
    bool open(const QString &path);
    bool init();

    QSqlDatabase db() const { return m_db; }

private:
    QSqlDatabase m_db;
};
