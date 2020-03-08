#ifndef NODETABLEMODEL_H
#define NODETABLEMODEL_H


#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "data.vw_node"


#include <QSqlTableModel>


class NodeTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit NodeTableModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns
    {
        column_pid,
        column_lat,
        column_lon,
        column_srid,
        column_geog,
        column_note,

        ColumnsNumber
    };
    Q_ENUM(Columns)
};

#endif // NODETABLEMODEL_H
