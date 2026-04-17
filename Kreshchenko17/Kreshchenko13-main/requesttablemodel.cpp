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

    const Request &r = m_items[index.row()];

    switch(index.column())
    {
    case 0: return r.id;
    case 1: return r.subject;
    case 2: return r.state;
    case 3: return r.level;
    case 4: return r.createdAt.toString("yyyy-MM-dd HH:mm");
    }

    return {};
}

QVariant RequestTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch(section)
    {
    case 0: return "ID";
    case 1: return "Subject";
    case 2: return "State";
    case 3: return "Level";
    case 4: return "Created";
    }

    return {};
}

void RequestTableModel::appendRequest(const Request &request)
{
    int row = m_items.size();

    beginInsertRows(QModelIndex(), row, row);
    m_items.append(request);
    endInsertRows();
}

void RequestTableModel::replaceRequest(int row, const Request &request)
{
    if(row < 0 || row >= m_items.size())
        return;

    m_items[row] = request;

    emit dataChanged(index(row,0), index(row,columnCount()-1));
}

void RequestTableModel::eraseRequest(int row)
{
    if(row < 0 || row >= m_items.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_items.removeAt(row);
    endRemoveRows();
}

Request RequestTableModel::requestAt(int row) const
{
    return m_items[row];
}
