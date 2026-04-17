#pragma once

#include <QSortFilterProxyModel>

class TicketFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit TicketFilterProxyModel(QObject *parent = nullptr);

    void setStatusFilter(const QString &status);
    void setPriorityFilter(const QString &priority);
    void setTextFilter(const QString &text);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const override;

private:
    QString m_status;
    QString m_priority;
    QString m_text;
};
