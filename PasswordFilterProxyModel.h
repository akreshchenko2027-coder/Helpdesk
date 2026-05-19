#ifndef PASSWORDFILTERPROXYMODEL_H
#define PASSWORDFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PasswordFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit PasswordFilterProxyModel(QObject *parent = nullptr);

    void setTextFilter(const QString &text);
    void setCategoryFilter(const QString &category);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_text;
    QString m_category;
};

#endif // PASSWORDFILTERPROXYMODEL_H
