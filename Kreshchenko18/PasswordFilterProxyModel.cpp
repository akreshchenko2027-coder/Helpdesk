#include "PasswordFilterProxyModel.h"

PasswordFilterProxyModel::PasswordFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

void PasswordFilterProxyModel::setTextFilter(const QString &text)
{
    m_text = text;
    invalidateFilter();
}

void PasswordFilterProxyModel::setCategoryFilter(const QString &category)
{
    m_category = category;
    invalidateFilter();
}

bool PasswordFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex titleIndex = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex categoryIndex = sourceModel()->index(sourceRow, 4, sourceParent);

    QString title = sourceModel()->data(titleIndex).toString();
    QString category = sourceModel()->data(categoryIndex).toString();

    bool textOk = m_text.isEmpty() || title.contains(m_text, Qt::CaseInsensitive);
    bool categoryOk = m_category.isEmpty() || m_category == "All" || category == m_category;

    return textOk && categoryOk;
}
