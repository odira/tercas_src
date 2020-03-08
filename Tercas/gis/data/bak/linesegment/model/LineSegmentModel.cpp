#include <QDate>

#include <vyborg.h>

#include "LineSegmentModel.h"

LineSegmentModel::LineSegmentModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant LineSegmentModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

//    if (role == Qt::DisplayRole)
//    {
//        switch (idx.column())
//        {

//        case linesegment_node1pid:
//        case linesegment_node2pid: {
//            int nodePid = QSqlTableModel::data(idx, Qt::DisplayRole).toInt();
//            return nodePid;
//            break;
////            QString strData = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
////            QDate dateData = QDate::fromString(strData, "yyyy-MM-dd");
////            return dateData.toString(QString("yyyy MMMM"));
////            break;
//        }

//        }
//    }

    return QSqlTableModel::data(idx, role);
}

QVariant LineSegmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount())
            return QVariant();

        if (role == Qt::DisplayRole) {
            switch (section)
            {

            case linesegment_pid:
                return QString(trUtf8("PID"));
                break;

            case linesegment_node1pid:
                return QString(trUtf8("PID\nnode 1"));
                break;

            case linesegment_node2pid:
                return QString(trUtf8("PID\nnode 2"));
                break;

            case linesegment_geog:
                return QString(trUtf8("Координаты"));
                break;

            case linesegment_noteru:
                return QString(trUtf8("Примечание"));
                break;

            }
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
