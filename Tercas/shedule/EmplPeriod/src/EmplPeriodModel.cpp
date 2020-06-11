#include <QDate>
#include <QtSql>
#include <QLocale>

#include "EmplPeriodModel.h"

EmplPeriodModel::EmplPeriodModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLENAME);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    generateRoleNames();
    select();
}

void EmplPeriodModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::DisplayRole] = QVariant(QString("display").toUtf8()).toByteArray();

    m_roleNames[Qt::UserRole + 1 + 0]  = QVariant(QString("pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 1]  = QVariant(QString("person_pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 2]  = QVariant(QString("person_fullname").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 3]  = QVariant(QString("person_shiftnum").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 4]  = QVariant(QString("activity_pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 5]  = QVariant(QString("activity_abbr").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 6]  = QVariant(QString("activity_activity").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 7]  = QVariant(QString("activity_color").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 8]  = QVariant(QString("activity_note").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 9]  = QVariant(QString("period").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 10] = QVariant(QString("start_date").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 11] = QVariant(QString("end_date").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 12] = QVariant(QString("duration").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 14] = QVariant(QString("note").toUtf8()).toByteArray();
}

QVariant EmplPeriodModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int row = idx.row();
    int col = idx.column();

    if (col < 0 || col > columnCount())
        return QVariant();

    if (row < 0 || row > rowCount())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (col == Columns::column_start_date || col == Columns::column_end_date)
            return QSqlTableModel::data(idx).toDate();
        else
            return QSqlTableModel::data(idx);
    }
    else if (role > Qt::UserRole)
    {
        int colIndex = role - Qt::UserRole - 1;
        QModelIndex index = this->index(row, colIndex);
        return this->data(index, Qt::DisplayRole);
    }
    else {
        return QSqlTableModel::data(idx, role);
    }
}

//QVariant EmplPeriodModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (orientation == Qt::Horizontal)
//    {
//        if (section < 0 || section >= columnCount()) {
//            return QVariant();
//        }

//        if (role == Qt::DisplayRole)
//        {
//            switch (section)
//            {

//            case column_person_fullname:
//                return QString(QObject::tr("Работник"));
//                // break;

//            case column_person_shiftnum:
//                return QString(tr("Смена"));
//                // break;

//            case column_activity_abbr:
//                return QVariant();
//                // break;

//            case column_activity_activity:
//                return QString(QObject::tr("Вид деятельности"));
//                // break;

//            case column_period:
//                return QString(QObject::tr("Период"));
//                // break;

//            case column_start_date:
//                return QString(QObject::tr("Дата начала"));
//                // break;

//            case column_end_date:
//                return QString(QObject::tr("Дата окончания"));
//                // break;

//            case column_duration:
//                return QString(QObject::tr("Кол-во\nдней"));
//                // break;

//            case column_note:
//                return QString(QObject::tr(("Примечание")));
//                // break;
//            }
//        }
//        else if (role == Qt::TextAlignmentRole)
//        {
//            if (section == column_period) {
//                return Qt::AlignHCenter;
//            }
//        }
//        else if (role == Qt::BackgroundColorRole)
//        {
//            return QColor("green");
//        }

//    }
//    else if (orientation == Qt::Vertical)
//    {
//        if (section >= rowCount())
//        {
//            return QVariant();
//        }

//        if (role == Qt::DisplayRole)
//        {
//            return section + 1;
//        }
//    }

//    return QSqlTableModel::headerData(section, orientation, role);
//}
