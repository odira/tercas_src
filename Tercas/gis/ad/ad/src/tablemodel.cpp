#include "tablemodel.h"
#include "declarations.h"
#include "vyborg.h"

TableModel::TableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant TableModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();

    if (col == ad_opr ||
        col == ad_intl)
    {
        switch (role) {
        case Qt::DisplayRole:
            return QString();
            break;
        case Qt::CheckStateRole:
                bool check = QSqlTableModel::data(idx, Qt::DisplayRole).toBool();
                if (check == true)
                    return Qt::Checked;
                else
                    return Qt::Unchecked;
            break;
        }
    }
    else if (col == ad_indxru)
    {
        switch (role) {
        case Qt::DisplayRole:
            QString data = QSqlTableModel::data(idx).toString();
            return lat2rus(data);
        }
    }
    else if (col == ad_department)
    {
        switch (role) {
        case Qt::DisplayRole:
            QString data = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
            if (data == "undefined")
                return QString();
            else
                return data;
            break;
        }
    }

    return QSqlTableModel::data(idx, role);
}
