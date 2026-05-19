#include "tickettablemodel.h"

TicketTableModel::TicketTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int TicketTableModel::rowCount(const QModelIndex &) const
{
    return m_tickets.size();
}

int TicketTableModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant TicketTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_tickets.size())
        return {};

    const Ticket &t = m_tickets[index.row()];

    // --- ВІДОБРАЖЕННЯ ---
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0: return t.id;
        case 1: return t.title;
        case 2: return t.status;
        case 3: return t.priority;
        case 4: return t.createdAt.toString("yyyy-MM-dd hh:mm");
        }
    }

    // --- ДЛЯ ПРАВИЛЬНОГО СОРТУВАННЯ ---
    if (role == Qt::UserRole)
    {
        switch(index.column())
        {
        case 0: return t.id;

        case 3: // Priority (кастомний порядок)
            if (t.priority == "Low") return 1;
            if (t.priority == "Medium") return 2;
            if (t.priority == "High") return 3;
            return 0;

        case 4: // Дата як число
            return t.createdAt.toSecsSinceEpoch();
        }
    }

    return QVariant();
}

QVariant TicketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0: return "ID";
        case 1: return "Title";
        case 2: return "Status";
        case 3: return "Priority";
        case 4: return "Created";
        }
    }

    return QVariant();
}

// --- ДОДАТИ ---
void TicketTableModel::addTicket(const Ticket &ticket)
{
    beginInsertRows(QModelIndex(), m_tickets.size(), m_tickets.size());
    m_tickets.append(ticket);
    endInsertRows();
}

// --- ОТРИМАТИ ---
Ticket TicketTableModel::ticketAt(int row) const
{
    if (row < 0 || row >= m_tickets.size())
        return {};
    return m_tickets[row];
}

// --- ВИДАЛИТИ ---
void TicketTableModel::removeTicket(int row)
{
    if (row < 0 || row >= m_tickets.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_tickets.removeAt(row);
    endRemoveRows();
}
