#include "ticketfilterproxymodel.h"

TicketFilterProxyModel::TicketFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void TicketFilterProxyModel::setStatusFilter(const QString &status)
{
    m_status = status;
    invalidateFilter();
}

void TicketFilterProxyModel::setPriorityFilter(const QString &priority)
{
    m_priority = priority;
    invalidateFilter();
}

void TicketFilterProxyModel::setTextFilter(const QString &text)
{
    m_text = text;
    invalidateFilter();
}

bool TicketFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex titleIndex = sourceModel()->index(sourceRow,1,sourceParent);
    QModelIndex statusIndex = sourceModel()->index(sourceRow,2,sourceParent);
    QModelIndex priorityIndex = sourceModel()->index(sourceRow,3,sourceParent);

    QString title = sourceModel()->data(titleIndex).toString();
    QString status = sourceModel()->data(statusIndex).toString();
    QString priority = sourceModel()->data(priorityIndex).toString();

    bool textOk = m_text.isEmpty() || title.contains(m_text, Qt::CaseInsensitive);
    bool statusOk = m_status.isEmpty() || status == m_status;
    bool priorityOk = m_priority.isEmpty() || priority == m_priority;

    return textOk && statusOk && priorityOk;
}
