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

    m_roleNames[Qt::UserRole + 1 + Columns::column_pid]                 = QVariant(QString("pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_pid]          = QVariant(QString("person_pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_surname]      = QVariant(QString("person_surname").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_name]         = QVariant(QString("person_name").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_middlename]   = QVariant(QString("person_middlename").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_position]     = QVariant(QString("person_position").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_shift_num]    = QVariant(QString("person_shift_num").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_person_sectors_pool] = QVariant(QString("person_sectors_pool").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_activity_pid]        = QVariant(QString("activity_pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_activity_abbr]       = QVariant(QString("activity_abbr").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_activity_activity]   = QVariant(QString("activity_activity").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_activity_color]      = QVariant(QString("activity_color").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_activity_note]       = QVariant(QString("activity_note").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_start_date]          = QVariant(QString("start_date").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_end_date]            = QVariant(QString("end_date").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_duration]            = QVariant(QString("duration").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + Columns::column_note]                = QVariant(QString("note").toUtf8()).toByteArray();
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
        if (col == Columns::column_start_date ||
            col == Columns::column_end_date)
            return QSqlTableModel::data(idx).toDate();
        else if (col == Columns::column_duration)
            return QSqlTableModel::data(idx).toInt();
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
