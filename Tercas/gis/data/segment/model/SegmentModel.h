#pragma once

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "data.vw_linesegment"

#include <QSqlTableModel>

class LineSegmentModel : public QSqlTableModel
{
    Q_OBJECT

public:
    LineSegmentModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns {
        linesegment_pid,
        linesegment_node1pid,
        linesegment_node2pid,
        linesegment_geog,
        linesegment_noteru,
    	ColumnsNumber
    };
    Q_ENUM(Columns)
};

