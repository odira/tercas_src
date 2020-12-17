#ifndef GISSECTORMODEL_H
#define GISSECTORMODEL_H

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "fir.vw_sector"

#include <QSqlTableModel>

class GisSectorModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit GisSectorModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE QVariant get(int row) const;

    enum Columns {
        sector_pid,
        sector_sectorpidarr,
        sector_label,
        sector_compound,
        sector_freq,
        sector_border,
        sector_geog,
        sector_nodepidarr,
        sector_phone,
        sector_npsdz,
        sector_npspdz,
        sector_color,
        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
    Columns m_columns;
};

#endif // GISSECTORMODEL_H
