#pragma once

#include <QAbstractTableModel>
#include "request.h"

class RequestTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RequestTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void appendRequest(const Request &request);
    void replaceRequest(int row, const Request &request);
    void eraseRequest(int row);

    Request requestAt(int row) const;

private:
    QList<Request> m_items;
};
