#include <QDate>

#include <vyborg.h>

#include "tablemodel.h"

TableModel::TableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant TableModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

//    if (role == Qt::DisplayRole)
//    {
//        switch (idx.column()) {
//        case month_monthyear: {
//            QString strData = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
//            QDate dateData = QDate::fromString(strData, "yyyy-MM-dd");
//            return dateData.toString(QString("yyyy MMMM"));
//            break;
//        }
//        }
//    }

    return QSqlTableModel::data(idx, role);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    if (orientation == Qt::Horizontal)
//    {
//        if (section >= columnCount())
//            return QVariant();

//        if (role == Qt::DisplayRole) {
//            switch (section) {
//            case month_monthyear:
//                return QString("Год/Месяц");
//                break;
//            case month_department:
//                return QString("Подразделение");
//                break;
//            case month_vol:
//                return QString("Количество\nобслуженных ВС");
//                break;
//            }
//        }
//    }

    return QSqlTableModel::headerData(section, orientation, role);
}
