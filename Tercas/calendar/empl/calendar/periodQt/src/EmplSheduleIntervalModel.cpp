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
//    case column_personpid:
//    {
//        if (role == Qt::DisplayRole)
//        {
//            int personpid = QSqlTableModel::data(idx).toInt();
//            QString queryString = QString("SELECT (surname || ' ' || LEFT(name, 1) || '.' || LEFT(middlename, 1) || '.') person_fullname "
//                                                               "FROM person.vw_person WHERE pid=%1").arg(personpid);
//            QSqlQuery query(queryString);
//            while (query.next()) {
//                QString person_fullname = query.value(0).toString();
//                return person_fullname;
//            }
//        }

//        break;
//    }
//    case column_activitypid:
//    {
//        if (role == Qt::DisplayRole)
//        {
//            int activitypid = QSqlTableModel::data(idx).toInt();
//            QString queryString = QString("SELECT activity FROM calendar.vw_activity WHERE pid=%1").arg(activitypid);
//            QSqlQuery query(queryString);
//            while (query.next()) {
//                QString activity = query.value(0).toString();
//                return activity;
//            }
//        }

//        break;
//    }

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
            return QColor("blue");
        }

        break;
    }

//    case additional_activityabbrcolor:
//    {
//        if (role == Qt::DisplayRole)
//        {
//            int row = idx.row();
//            int col = fieldIndex("activitypid");
//            int activitypid = QSqlTableModel::data(index(row, col)).toInt();
//            QString queryString = QString("SELECT abbr FROM calendar.vw_activity WHERE pid=%1").arg(activitypid);
//            QSqlQuery query(queryString);
//            while (query.next()) {
//                QString abbrString = query.value(0).toString();
//                return abbrString;
//            }
//        }
//        else if (role == Qt::TextAlignmentRole)
//        {
//            return Qt::AlignCenter;
//        }
//        else if (role == Qt::ForegroundRole)
//        {
//            return QColor("black");
//        }
//        else if (role == Qt::BackgroundRole)
//        {
//            int row = idx.row();
//            int col = fieldIndex("activitypid");
//            int activitypid = QSqlTableModel::data(index(row, col)).toInt();
//            QString queryString = QString("SELECT color FROM calendar.vw_activity WHERE pid=%1").arg(activitypid);
//            QSqlQuery query(queryString);
//            while (query.next()) {
//                QString colorString = query.value(0).toString();
//                if (!colorString.isEmpty()) {
//                    return QColor(colorString);
//                } else {
//                    return QVariant();
//                }
//            }
//        }
//        else if (role == Qt::SizeHintRole)
//        {
//            return QSize(38, 20);
//        }

//        break;
//    }
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
                return QString(QObject::tr("Работник"));
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
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
