#pragma once

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "rts.vw_rlp"

#include <QSqlTableModel>

class GisRlpModel : public QSqlTableModel
{
    Q_OBJECT

public:
    GisRlpModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns {
        rlp_pid,
        rlp_name,
        rlp_nodepid,
        rlp_nodegeog,
        rlp_nodenoteru,
        rlp_noteru,
        ColumnsNumber
    };
    Q_ENUM(Columns)
};
