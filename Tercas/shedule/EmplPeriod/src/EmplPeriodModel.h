#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLENAME "shedule.vw_empl_shedule"

#include <QSqlTableModel>

class EmplPeriodModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplPeriodModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QHash<int, QByteArray> roleNames() const { return m_roleNames; }

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    enum Columns
    {
        column_pid,
        column_person_pid,
        column_person_fullname,
        column_person_shiftnum,
        column_activity_pid,
        column_activity_abbr,
        column_activity_activity,
        column_activity_color,
        column_activity_note,
        column_period,
        column_start_date,
        column_end_date,
        column_duration,
        column_note,

        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
};
