#ifndef CSVTICKETREPOSITORY_H
#define CSVTICKETREPOSITORY_H

#include "requestentry.h"
#include <QList>
#include <QString>

class CsvTicketRepository
{
public:
    explicit CsvTicketRepository(const QString &filePath);

    QList<RequestEntry> loadAll() const;
    bool saveAll(const QList<RequestEntry> &items) const;

private:
    QString m_filePath;

    RequestEntry parseRow(const QString &line) const;
    QString toCsvRow(const RequestEntry &entry) const;
};

#endif
