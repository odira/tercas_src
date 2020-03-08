#include <QDate>

#include "GisRlpModel.h"

GisRlpModel::GisRlpModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant GisRlpModel::data(const QModelIndex &idx, int role) const
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

QVariant GisRlpModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount())
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            switch (section) {

            case rlp_name:
                return QString("РЛП");
                // break; // will never be executed

            case rlp_nodegeog:
                return QString(trUtf8("Координаты"));
                // break; // will never be executed

            case rlp_noteru:
                return QString("Примечание");
                // break; // will never be executed
            }
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
