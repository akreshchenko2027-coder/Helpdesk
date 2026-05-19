#ifndef REQUESTTABLEMODEL_H
#define REQUESTTABLEMODEL_H

#include <QAbstractTableModel>
#include "requestentry.h"

class RequestTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RequestTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &, int role) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;

    void setItems(const QList<RequestEntry> &items);
    QList<RequestEntry> items() const;

    void addItem(const RequestEntry &item);

private:
    QList<RequestEntry> m_items;
};

#endif
