#include <QDate>
#include <QtSql>
#include <QLocale>

#include "EmplSheduleIntervalModel.h"

EmplSheduleIntervalModel::EmplSheduleIntervalModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLENAME);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant EmplSheduleIntervalModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    switch (col)
    {

    case column_person_surname:
    {
        if (role == Qt::FontRole)
        {
            QFont currentFont;
            currentFont.setBold(true);
            return currentFont;
        }

        break;
    }

    case column_activity_abbr:
    {
        if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }
        else if (role == Qt::ForegroundRole)
        {
            return QColor("black");
        }
        else if (role == Qt::BackgroundRole)
        {
            QModelIndex bgIndex = createIndex(idx.row(), column_activity_color);
            QString bgColorString = QSqlTableModel::data(bgIndex, Qt::DisplayRole).toString();
            return QColor(bgColorString);
        }
        else if (role == Qt::SizeHintRole)
        {
            return QSize(38, 20);
        }

        break;
    }

    case column_start_date:
    {
        if (role == Qt::DisplayRole)
        {
            QDate date = QSqlTableModel::data(idx).toDate();
            QLocale ruLocale(QLocale::Russian);
            QString data = ruLocale.toString(date, QString("dd MMMM yyyy"));

            return data;
        }
        else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignCenter;
        }

        break;
    }

    case column_end_date:
    {
        if (role == Qt::DisplayRole)
        {
            QDate date = QSqlTableModel::data(idx).toDate();
            QLocale ruLocale(QLocale::Russian);
            QString data = ruLocale.toString(date, QString("dd MMMM yyyy"));

            QModelIndex startIdx = index(idx.row(), column_start_date);
            QDate startDate = QSqlTableModel::data(startIdx).toDate();
            if (startDate == date)
                return QVariant();

            return data;
        } else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignCenter;
        }

        break;
    }

    case column_duration:
    {
        if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }
        else if (role == Qt::ForegroundRole)
        {
            return QColor("lightblue");
        }

        break;
    }
    }

    return QSqlTableModel::data(idx, role);
}

QVariant EmplSheduleIntervalModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section < 0 || section >= columnCount()) {
            return QVariant();
        }

        if (role == Qt::DisplayRole)
        {
            switch (section)
            {

            case column_person_surname:
                return QString(QObject::tr("Фамилия"));
                // break;

            case column_person_name:
                return QString(tr("Имя"));
                // break;

            case column_person_middlename:
                return QString(tr("Отчество"));
                // break;

            case column_person_position:
                return QString(tr("Должность"));
                // break;

            case column_person_sectors_pool:
                return QString(tr("Направление"));
                // break;

            case column_person_shift_num:
                return QString(tr("Смена"));
                // break;

            case column_activity_abbr:
                return QVariant();
                // break;

            case column_activity_activity:
                return QString(QObject::tr("Вид деятельности"));
                // break;

            case column_valid:
                return QString(QObject::tr("Действителен"));
                // break;

            case column_start_date:
                return QString(QObject::tr("Дата начала"));
                // break;

            case column_end_date:
                return QString(QObject::tr("Дата окончания"));
                // break;

            case column_duration:
                return QString(QObject::tr("Кол-во\nдней"));
                // break;

            case column_note:
                return QString(QObject::tr(("Примечание")));
                // break;
            }
        }
        else if (role == Qt::BackgroundColorRole)
        {
            return QColor("green");
        }

        return QVariant();

    }
    else if (orientation == Qt::Vertical)
    {
        if (section >= rowCount())
        {
            return QVariant();
        }

        if (role == Qt::DisplayRole)
        {
            return section + 1;
        }

        return QVariant();
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
