#include <QSql>
#include <vyborg.h>

#include "NodeTableModel.h"


NodeTableModel::NodeTableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLENAME);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

#include <QDebug>
QVariant NodeTableModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid()) {
        return QVariant();
    }

    if (idx.row() > rowCount())
        return QVariant();


    int col = idx.column();


    switch (col)
    {

    case NodeTableModel::Columns::column_lat:
    {
        if (role == Qt::DisplayRole)
        {
            qreal lat = QSqlTableModel::data(idx, role).toReal();
            QString latStr = QString::number(lat, 'f', 15);
            return latStr;
        }
        else if (role == Qt::TextAlignmentRole)
        {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }

        break;
    }

    case NodeTableModel::Columns::column_lon:
    {
        if (role == Qt::DisplayRole)
        {
            qreal lon = QSqlTableModel::data(idx, role).toReal();
            QString lonStr = QString::number(lon, 'f', 15);
            return lonStr;
        }
        else if (role == Qt::TextAlignmentRole)
        {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }

        break;
    }

//    case NodeTableModel::Columns::column_geog:
//    {
//        if (role == Qt::DisplayRole)
//        {
//            QString geogStr = QSqlTableModel::data(idx, role).toString();
//            QString queryStr = QString("SELECT ST_AsLatLonText('%1'::geometry, 'D° M'' S.SSS\"C')").arg(geogStr);
//            QSqlQuery query(queryStr);
//            while (query.next()) {
//                QString coordStr = query.value(0).toString();
//                return coordStr;
//            }
//        }

//        break;
//    }

//    case NodeTableModel::Columns::column_lat:
//    {
//        if (role == Qt::DisplayRole) {
//            QString latStr = QString(tr("SELECT ST_X('%1'::geometry").arg())
//        }
//    }


    } // switch


    return QSqlTableModel::data(idx, role);
}

//bool NodeTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!index.isValid())
//        return false;

//    if (index.row() > rowCount())
//        return false;

//    if (index.column() > columnCount())
//        return false;


//    int col = index.column();
//    switch (col)
//    {

//    case NodeTableModel::Columns::column_lat:
//    case NodeTableModel::Columns::column_lon:
//    {
//        qreal data = value.toReal();
//        return QSqlTableModel::setData(index, data);
//    }

//    case NodeTableModel::Columns::column_srid:
//    {
//        int data = value.toInt();
//        return QSqlTableModel::setData(index, data);
//    }

//    } // switch


//    return QSqlTableModel::setData(index, value);
//}

QVariant NodeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section < 0 || section > columnCount())
            return QVariant();

        if (role == Qt::DisplayRole)
        {

            switch (section)
            {

            case column_pid:
                return QString(tr("PID"));

            case column_lat:
                return QString(tr("Широта"));

            case column_lon:
                return QString(tr("Долгота"));

            case column_srid:
                return QString(tr("SRID"));

//            case column_geog:
//                return QString(tr("Координаты"));

            case column_note:
                return QString(tr("Примечание"));

            } // switch (section)

        } // Qt::DisplayRole
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
