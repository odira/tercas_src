#pragma once

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "fir.vw_sectorspool"

#include <QSqlTableModel>

class GisSectorsPoolModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit GisSectorsPoolModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE QVariant get(int row) const;

    enum Columns {
        sectorspool_pid,
        sectorspool_name,
        sectorspool_sectorpidarr,
        sectorspool_color,
        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
    Columns m_columns;
};
