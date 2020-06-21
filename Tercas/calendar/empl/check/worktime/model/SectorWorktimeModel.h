#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLENAME "shedule.vw_empl_sector_worktime"

#include <QSqlTableModel>


class SectorWorktimeModel : public QSqlTableModel
{
    Q_OBJECT

public:
    SectorWorktimeModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    enum Columns {

        column_pid,
        column_personpid,
        column_personfullname,
        column_sectorpid,
        column_sectorlabel,
        column_sectorcolor,
        column_sector_pos,
        column_range,
        column_startdatetime,
        column_enddatetime,
        column_startdate,
        column_starttime,
        column_enddate,
        column_endtime,
        column_interval,
        column_note,

        ColumnsNumber
    };
    Q_ENUM(Columns)
};

