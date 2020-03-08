#include <QtWidgets>

#include "tablemodel.h"
#include "declarations.h"


TableModel::TableModel(QObject *parent)
    : QSqlTableModel(parent)
{
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    return QAbstractItemModel::flags(index);
}
