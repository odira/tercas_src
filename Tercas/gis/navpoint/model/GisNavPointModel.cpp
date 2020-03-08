#include <QDate>

#include <vyborg.h>

#include "GisNavPointModel.h"

GisNavPointModel::GisNavPointModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant GisNavPointModel::data(const QModelIndex &idx, int role) const
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

//    if (role == Qt::DisplayRole)
//    {
//        switch (idx.column()) {

//        case GisNavPointModel::Columns::navpoint_navpointtype: {
//            int str
//        }

//        } // switch
//    }

    return QSqlTableModel::data(idx, role);
}

QVariant GisNavPointModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount())
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            switch (section)
            {

            case navpoint_pid:
                return QString(trUtf8("PID"));
                break; // will never be executed

            case navpoint_navpoint:
                return QString(trUtf8("Наименование"));
                break; // will never be executed

            case navpoint_ident:
                return QString(trUtf8("Позывной"));
                break; // will never be executed

            case navpoint_navpointtype:
                return QString(trUtf8("Тип"));
                break; // will never be executed

            case navpoint_frequency:
                return QString(trUtf8("Частота"));
                break; // will never be executed

            case navpoint_nodepid:
                return QString(trUtf8("node\nPID"));
                break; // will never be executed

            case navpoint_nodegeog:
                return QString(trUtf8("Координаты"));
                break; // will never be executed

            case navpoint_noteru:
                return QString(trUtf8("Примечание"));
                break; // will never be executed

            } // switch
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
