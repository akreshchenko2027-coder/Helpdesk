#include "csvticketrepository.h"
#include <QFile>
#include <QTextStream>
#include <QSaveFile>
#include <QStringConverter>

CsvTicketRepository::CsvTicketRepository(const QString &filePath)
    : m_filePath(filePath)
{
}

QList<RequestEntry> CsvTicketRepository::loadAll() const
{
    QList<RequestEntry> items;

    QFile file(m_filePath);
    if (!file.exists())
        return items;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return items;

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    if (!in.atEnd())
        in.readLine();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.isEmpty()) continue;
        items.append(parseRow(line));
    }

    return items;
}

bool CsvTicketRepository::saveAll(const QList<RequestEntry> &items) const
{
    QSaveFile file(m_filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "Id,Title,Priority,Status,Description,CreatedAt\n";

    for (const RequestEntry &e : items)
        out << toCsvRow(e) << "\n";

    return file.commit();
}

RequestEntry CsvTicketRepository::parseRow(const QString &line) const
{
    QStringList p = line.split(',');

    RequestEntry e;
    e.id = p.value(0).toInt();
    e.title = p.value(1);
    e.priority = p.value(2);
    e.status = p.value(3);
    e.description = p.value(4);
    e.createdAt = QDateTime::fromString(p.value(5), Qt::ISODate);

    return e;
}

QString CsvTicketRepository::toCsvRow(const RequestEntry &e) const
{
    return QString("%1,%2,%3,%4,%5,%6")
    .arg(e.id)
        .arg(e.title)
        .arg(e.priority)
        .arg(e.status)
        .arg(e.description)
        .arg(e.createdAt.toString(Qt::ISODate));
}
