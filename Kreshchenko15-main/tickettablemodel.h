#pragma once

#include <QAbstractTableModel>
#include "ticket.h"

class TicketTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TicketTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addTicket(const Ticket &ticket);
    Ticket ticketAt(int row) const;
    void removeTicket(int row);

private:
    QList<Ticket> m_tickets;
};
