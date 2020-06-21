#include <QDate>

#include <vyborg.h>
#include "SectorWorktimeModel.h"


SectorWorktimeModel::SectorWorktimeModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant SectorWorktimeModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    int row = idx.row();


    switch (col)
    {

    case column_personfullname:

        if (role == Qt::FontRole)
        {
            QFont font;
            font.setBold(true);
            return font;
        }

        break;


    case column_sectorlabel:

        if (role == Qt::FontRole)
        {
            QFont font;
            font.setBold(true);
            return font;
        }
        else if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }
        else if (role == Qt::BackgroundRole)
        {
            QString colorStr = QSqlTableModel::data(index(row, column_sectorcolor), Qt::DisplayRole).toString();
            QColor color = QColor(colorStr);
            return color;
        }

        break;


    case column_sector_pos:

        if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }

        break;


    case column_startdate:
    case column_enddate:

        if (role == Qt::DisplayRole)
        {
            QDate date = QSqlTableModel::data(idx).toDate();
            QLocale ruLocale(QLocale::Russian);
            QString data = ruLocale.toString(date, QString("dd MMMM yyyy"));
            return data;
        }

        break;


    case column_starttime:
    case column_endtime:

        if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }

        break;


    case column_interval:

        if (role == Qt::DisplayRole)
        {
            QTime timeInterval = QSqlTableModel::data(index(row, column_interval), Qt::DisplayRole).toTime();
            QString timeIntervalStr = timeInterval.toString("hh : mm");
            return timeIntervalStr;
        }
        else if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }
        else if (role == Qt::ForegroundRole)
        {
            return QColor("blue");
        }

        break;


    } // switch


    return QSqlTableModel::data(idx, role);
}

QVariant SectorWorktimeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount())
            return QVariant();

        if (role == Qt::DisplayRole) {

            switch (section)
            {

            case column_personfullname:
                return QString(tr("Работник"));

            case column_sectorlabel:
                return QString(tr("Обозначение\nсектора"));

            case column_sector_pos:
                return QString(tr("Место"));

            case column_startdate:
                return QString(tr("Дата\nначала"));

            case column_starttime:
                return QString(tr("Время\nначала"));

            case column_enddate:
                return QString(tr("Дата\nокончания"));

            case column_endtime:
                return QString(tr("Время\nокончания"));

            case column_interval:
                return QString(tr("Продолжительность\nработы"));

            case column_note:
                return QString(tr("Примечание"));

            } // switch

        }
        else if (role == Qt::FontRole)
        {

            QFont font;
            font.setBold(true);
            return font;

        }

    }

    return QSqlTableModel::headerData(section, orientation, role);
}
