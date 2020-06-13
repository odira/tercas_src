#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLENAME "shedule.vw_empl_period"

#include <QSqlTableModel>

class EmplPeriodModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplPeriodModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;

    enum Columns
    {
        Column_pid = 0,
        Column_person_pid,          // 1
        Column_person_surname,      // 2
        Column_person_name,         // 3
        Column_person_middlename,   // 4
        Column_person_position,     // 5
        Column_person_shift_num,    // 6
        Column_person_sectors_pool, // 7
        Column_activity_pid,        // 8
        Column_activity_abbr,       // 9
        Column_activity_activity,   // 10
        Column_activity_color,      // 11
        Column_activity_note,       // 12
        Column_start_date,          // 13
        Column_end_date,            // 14
        Column_duration,            // 15
        Column_note,                // 16

        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
};
