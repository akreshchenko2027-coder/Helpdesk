#include "PasswordTableModel.h"
#include <QDateTime>

PasswordTableModel::PasswordTableModel(PasswordRepository *repository, QObject *parent)
    : QAbstractTableModel(parent), m_repository(repository) {}

int PasswordTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.size();
}

int PasswordTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6; // ID, Title, Login, Site, Category, UpdatedAt (Пароль приховаємо)
}

QVariant PasswordTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_items.size()) return {};

    const PasswordRecord &item = m_items[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0: return item.id;
        case 1: return item.title;
        case 2: return item.login;
        case 3: return item.site;
        case 4: return item.category;
        case 5: return item.updatedAt;
        default: return {};
        }
    }
    return {};
}

QVariant PasswordTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
    switch (section) {
    case 0: return "ID";
    case 1: return "Title";
    case 2: return "Login";
    case 3: return "Website";
    case 4: return "Category";
    case 5: return "Updated";
    default: return {};
    }
}

Qt::ItemFlags PasswordTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    // Дозволяємо редагувати всі стовпці крім ID (0) та дати (5)
    if (index.column() > 0 && index.column() < 5) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool PasswordTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) return false;

    PasswordRecord updated = m_items[index.row()];
    QString strVal = value.toString();

    switch (index.column()) {
    case 1: updated.title = strVal; break;
    case 2: updated.login = strVal; break;
    case 3: updated.site = strVal; break;
    case 4: updated.category = strVal; break;
    default: return false;
    }

    updated.updatedAt = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    if (!m_repository->update(updated)) return false;

    m_items[index.row()] = updated;
    emit dataChanged(index, this->index(index.row(), 5), {Qt::DisplayRole, Qt::EditRole});
    return true;
}

void PasswordTableModel::setItems(const QList<PasswordRecord> &items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
}

const PasswordRecord& PasswordTableModel::itemAt(int row) const
{
    return m_items[row];
}
