#pragma once

#define PGSQL_TABLENAME "calendar.vw_empl_period"

#include <QSqlTableModel>


class EmplSheduleIntervalModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplSheduleIntervalModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    enum Columns
    {
        column_pid = 0,
        column_person_pid,          // 1
        column_person_surname,      // 2
        column_person_name,         // 3
        column_person_middlename,   // 4
        column_person_position,     // 5
        column_person_shift_num,    // 6
        column_person_sectors_pool, // 7
        column_activity_pid,        // 8
        column_activity_abbr,       // 9
        column_activity_activity,   // 10
        column_activity_color,      // 11
        column_activity_note,       // 12
        column_start_date,          // 13
        column_end_date,            // 14
        column_duration,            // 15
        column_note,                // 16

        ColumnsNumber
    };
    Q_ENUM(Columns)
};
