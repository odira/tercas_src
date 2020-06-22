#include <QDate>

#include <vyborg.h>

#include "../entactivityQt/src/declarations.h"
#include "EntActivityModel.h"

EntActivityModel::EntActivityModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant EntActivityModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid()) {
        return QVariant();
    }

    int col = idx.column();
    switch (col)
    {
    case entactivity_abbr:
    {
        if (role == Qt::BackgroundRole)
        {
            QString colorStr = QSqlTableModel::data(index(idx.row(), entactivity_color), Qt::DisplayRole).toString();
            if (!colorStr.isNull()) {
                return QColor(colorStr);
            } else {
                return QColor("white");
            }
        }

        break;
    }
    }

//    if (role == Qt::DisplayRole)
//    {
//        switch (idx.column()) {
//        case month_monthyear: {
//            QString strData = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
//            QDate dateData = QDate::fromString(strData, "yyyy-MM-dd");
//            return dateData.toString(QString("yyyy MMMM"));
//            break;
//        }
//        }
//    }

    return QSqlTableModel::data(idx, role);
}

QVariant EntActivityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount()) {
            return QVariant();
        }

        if (role == Qt::DisplayRole)
        {
            switch (section)
            {
            case entactivity_pid:
                return QString(trUtf8("PID"));
                break;

            case entactivity_color:
                return QString(trUtf8("Цвет"));
                break;

            case entactivity_abbr:
                return QVariant();
                break;

            case entactivity_entactivity:
                return QString(trUtf8("Активность"));
                break;

            case entactivity_noteru:
                return QString(trUtf8("Примечание"));
                break;
            }
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
