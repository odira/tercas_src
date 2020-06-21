#pragma once

#define PGSQL_TABLENAME "shedule.vw_activity"

#include <QSqlTableModel>

class EmplActivityModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplActivityModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::EditRole) const;

    enum Columns {

        activity_pid,
        activity_color,
        activity_abbr,
        activity_activity,
        activity_note,
        activity_path,

        ColumnsCount
    };
    Q_ENUM(Columns)
};
