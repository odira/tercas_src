#include <QDate>

#include "SafetyModel.h"

SafetyModel::SafetyModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable("safety.vw_safety");
    generateRoleNames();
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

void SafetyModel::generateRoleNames()
{
    m_roleNames.clear();

    for (int i = 0; i < columnCount(); i++)
        m_roleNames[Qt::UserRole + 1 + i] =
                QVariant((headerData(i, Qt::Horizontal)).toString().toUtf8()).toByteArray();
}

QVariant SafetyModel::data(const QModelIndex &indx, int role) const
{
    if (!indx.isValid())
        return QVariant();

    if (indx.row() >= rowCount())
        return QVariant();

    int row = indx.row();
    int col = indx.column();

    if (role == Qt::DisplayRole)
    {
        if (col == 1)
            return QSqlTableModel::data(indx, role).toDateTime().toString("yyyy-MM-dd");
        else
            return QSqlTableModel::data(indx, role);
    }
    else if (role > Qt::UserRole)
    {
        QModelIndex index = QSqlTableModel::index(row, role - Qt::UserRole - 1);
        QVariant data = this->data(index, Qt::DisplayRole);
        if (data.isNull())
            return QVariant();
        return data;
    }

    return QVariant();
}

QVariant SafetyModel::get(int row) const
{
    QMap<QString, QVariant> data;

    QHashIterator<int, QByteArray> iterator(roleNames());
    while (iterator.hasNext()) {
        iterator.next();
        data.insert(iterator.value(),
                    this->data(index(row, iterator.key() - Qt::UserRole - 1), Qt::DisplayRole));
    }

    return data;
}
