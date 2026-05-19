#ifndef PASSWORDTABLEMODEL_H
#define PASSWORDTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "PasswordRecord.h"
#include "PasswordRepository.h"

class PasswordTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PasswordTableModel(PasswordRepository *repository, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void setItems(const QList<PasswordRecord> &items);
    const PasswordRecord& itemAt(int row) const;

private:
    QList<PasswordRecord> m_items;
    PasswordRepository *m_repository;
};

#endif
