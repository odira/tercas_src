#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLENAME "skeleton.vw_skeleton"

#include <QSqlTableModel>

class TableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns {
    	skeleton_pid,           
    	skeleton_skeleton,        
    	ColumnsNumber
    };
    Q_ENUM(Columns)
};

