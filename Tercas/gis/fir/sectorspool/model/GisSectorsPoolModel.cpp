#include <QFont>
#include <QBrush>
#include <QColor>

#include "GisSectorsPoolModel.h"

GisSectorsPoolModel::GisSectorsPoolModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLENAME);
    generateRoleNames();
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

void GisSectorsPoolModel::generateRoleNames()
{
    m_roleNames.clear();
    for (int i = 0; i < columnCount(); i++) {
        m_roleNames[Qt::UserRole + 1 + i] =
                QVariant((headerData(i, Qt::Horizontal, Qt::UserRole)).toString().toUtf8()).toByteArray();
    }
}

QHash<int, QByteArray> GisSectorsPoolModel::roleNames() const
{
    return m_roleNames;
}

QVariant GisSectorsPoolModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid()) {
        return QVariant();
    }

    int row = idx.row();
    int col = idx.column();

    if (row < 0 || row > rowCount())
        return QVariant();

    if (role < Qt::UserRole)
    {
        switch (col)
        {
        case sectorspool_name:

            if (role == Qt::FontRole)
            {
                QFont font = QFont();
                font.setBold(true);
                return font;
            }

            break;

        case sectorspool_sectorpidarr:

            if (role == Qt::DisplayRole)
            {
                QString sectorPidArrStr = QSqlTableModel::data(idx).toString();
                return sectorPidArrStr;
            }

            break;

        } //switch (col)
    }
    else if (role >= Qt::UserRole)
    {
        col = role - Qt::UserRole - 1;
        return QSqlTableModel::data(createIndex(row, col), Qt::DisplayRole);
    }

    return QSqlTableModel::data(idx, role);
}

QVariant GisSectorsPoolModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section < 0 || section >= columnCount()) {
            return QVariant();
        }

        if (role == Qt::DisplayRole)
        {

            switch (section) {
            case sectorspool_pid:
                return QString(trUtf8("PID"));
                break;

            case sectorspool_name:
                return QString(trUtf8("Полное\nнаименование"));
                break;

            case sectorspool_sectorpidarr:
                return QString(trUtf8("Составные\nсектора"));
                break;

            case sectorspool_color:
                return QString(trUtf8("Цвет"));
                break;
            }
        }
        else if (role == Qt::UserRole) {
            return QSqlTableModel::headerData(section, orientation, Qt::DisplayRole);
        }

    }

    return QSqlTableModel::headerData(section, orientation, role);
}

bool GisSectorsPoolModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    int col = index.column();
    switch (role) {
    case Qt::EditRole:

        if (col == sectorspool_sectorpidarr)
        {
            QString sectorPidArrStr = value.toString();
            return QSqlTableModel::setData(index, sectorPidArrStr);
        }

        break;
    }

    return QSqlTableModel::setData(index, value, role);
}

QVariant GisSectorsPoolModel::get(int row) const
{
    if (row < 0 || row >= rowCount())
        return QVariant();

    QMap<QString, QVariant> data;
    QHashIterator<int, QByteArray> iterator(roleNames());
    while (iterator.hasNext()) {
        iterator.next();
        data.insert(iterator.value(), QSqlTableModel::data(index(row, iterator.key() - Qt::UserRole - 1)).toString());
    }
    return data;
}
