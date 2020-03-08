#pragma once

#include <QSqlTableModel>

#define PGSQL_TABLENAME "shedule.vw_activity"


class ActivityModel : public QSqlTableModel
{
    Q_OBJECT

public:
    ActivityModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::EditRole) const;

    enum Columns {

        pid,
        color,
        abbr,
        activity,
        note,
        path,

//        activity_pid,
//        activity_cover,
//        activity_color,
//        activity_abbr,
//        activity_activity,
//        activity_note,

        ColumnsCount
    };
};
