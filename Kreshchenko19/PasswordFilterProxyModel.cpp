#include "PasswordFilterProxyModel.h"

PasswordFilterProxyModel::PasswordFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

void PasswordFilterProxyModel::setTextFilter(const QString &text) { m_text = text; invalidateFilter(); }
void PasswordFilterProxyModel::setCategoryFilter(const QString &category) { m_category = category; invalidateFilter(); }

bool PasswordFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QString title = sourceModel()->data(sourceModel()->index(sourceRow, 1, sourceParent)).toString();
    QString category = sourceModel()->data(sourceModel()->index(sourceRow, 4, sourceParent)).toString();
    return (m_text.isEmpty() || title.contains(m_text, Qt::CaseInsensitive)) &&
           (m_category.isEmpty() || m_category == "All" || category == m_category);
}
