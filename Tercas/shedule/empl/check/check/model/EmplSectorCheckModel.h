#ifndef EMPLSECTORCHECKMODEL_H
#define EMPLSECTORCHECKMODEL_H

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLENAME "shedule.vw_empl_sector_check"

#include <QSqlTableModel>

class EmplSectorCheckModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplSectorCheckModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE QVariant get(int row) const;

    Q_INVOKABLE void reload();
    Q_INVOKABLE void applyFilter(const QString &filter);

private:
    void generateRoleNames();

public:
    enum Columns {

        column_pid = 0,
        column_personpid,
        column_personfullname,
        column_sectorpid,
        column_sectorlabel,
        column_sectorcolor,
        column_date,
        column_type,
        column_note,

        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    QHash<int, QByteArray> m_roleNames;
};

#endif // EMPLSECTORCHECKMODEL_H
