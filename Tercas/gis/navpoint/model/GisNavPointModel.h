#pragma once

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "navpoint.vw_navpoint"

#include <QSqlTableModel>

class GisNavPointModel : public QSqlTableModel
{
    Q_OBJECT

public:
    GisNavPointModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns {
        navpoint_pid,
        navpoint_navpoint,
        navpoint_ident,
        navpoint_navpointtype,
        navpoint_frequency,
        navpoint_nodepid,
        navpoint_nodegeog,
        navpoint_noteru,
    	ColumnsNumber
    };
    Q_ENUM(Columns)
};

