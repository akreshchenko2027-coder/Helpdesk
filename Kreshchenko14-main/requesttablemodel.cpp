#include "requesttablemodel.h"

RequestTableModel::RequestTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int RequestTableModel::rowCount(const QModelIndex &) const
{
    return m_items.size();
}

int RequestTableModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant RequestTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const RequestEntry &e = m_items[index.row()];

    switch (index.column())
    {
    case 0: return e.id;
    case 1: return e.title;
    case 2: return e.priority;
    case 3: return e.status;
    case 4: return e.createdAt.toString("yyyy-MM-dd HH:mm");
    }

    return {};
}

QVariant RequestTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section)
    {
    case 0: return "ID";
    case 1: return "Title";
    case 2: return "Priority";
    case 3: return "Status";
    case 4: return "Created";
    }

    return {};
}

void RequestTableModel::setItems(const QList<RequestEntry> &items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
}

QList<RequestEntry> RequestTableModel::items() const
{
    return m_items;
}

void RequestTableModel::addItem(const RequestEntry &item)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(item);
    endInsertRows();
}
