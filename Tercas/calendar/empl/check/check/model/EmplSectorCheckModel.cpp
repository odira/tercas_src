#include <QtSql>
#include <QDate>

#include "EmplSectorCheckModel.h"


EmplSectorCheckModel::EmplSectorCheckModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLENAME);
    generateRoleNames();
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

void EmplSectorCheckModel::generateRoleNames()
{
    m_roleNames.clear();
    for (int i = 0; i < columnCount(); i++)
        m_roleNames[Qt::UserRole + 1 + i] = QVariant((headerData(i, Qt::Horizontal, Qt::UserRole)).toString().toUtf8()).toByteArray();
}

QHash<int, QByteArray> EmplSectorCheckModel::roleNames() const
{
    return m_roleNames;
}

QVariant EmplSectorCheckModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid()) {
        return QVariant();
    }

    if (idx.row() > rowCount())
        return QVariant();

    if (role < Qt::UserRole)
    {
        int col = idx.column();
        int row = idx.row();

        switch (col)
        {

        case column_personfullname:

            if (role == Qt::FontRole)
            {
                QFont currentFont;
                currentFont.setBold(true);
                return currentFont;
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


        case column_date:

            if (role == Qt::DisplayRole)
            {
                QDate date = QSqlTableModel::data(idx).toDate();
                QLocale ruLocale(QLocale::Russian);
                QString dateStr = ruLocale.toString(date, QString("dd MMMM yyyy"));
                return dateStr;
            }
            else if (role == Qt::TextAlignmentRole)
            {
                return Qt::AlignCenter;
            }

            break;

        } // switch (col)

    }
    else // role > Qt::UserRole
    {
        QModelIndex indx = QSqlTableModel::index(idx.row(), role - Qt::UserRole - 1);
        QVariant data = QSqlTableModel::data(indx, Qt::DisplayRole);
        if (data.isNull())
            return QVariant();
        return data;
    }

    return QSqlTableModel::data(idx, role);
}

QVariant EmplSectorCheckModel::headerData(int section, Qt::Orientation orientation, int role) const
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

            case column_pid:
                return QString(tr("PID"));

            case column_personpid:
                return QString(tr("Работник PID"));

            case column_personfullname:
                return QString(tr("Работник"));

            case column_sectorpid:
                return QString(tr("Сектор PID"));

            case column_sectorlabel:
                return QString(tr("Обозначение\nсектора"));

            case column_sectorcolor:
                return QString(tr("Цвет"));

            case column_date:
                return QString(tr("Дата"));

            case column_type:
                return QString(tr("Детализация\nпроверки"));

            case column_note:
                return QString(tr("Примечание"));

            } // switch
        }
        else if (role == Qt::UserRole)
        {
            return QSqlTableModel::headerData(section, orientation, Qt::DisplayRole);
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}

QVariant EmplSectorCheckModel::get(int row) const
{
    if (row < 0 || row >= rowCount())
        return QVariant();

    QMap<QString, QVariant> data;
    QHashIterator<int, QByteArray> iterator(roleNames());
    while (iterator.hasNext()) {
        iterator.next();
        data.insert(iterator.value(), QSqlTableModel::data(index(row, iterator.key() - Qt::UserRole - 1)).toString());
    }
    return data;
}

void EmplSectorCheckModel::reload()
{
    select();
}

void EmplSectorCheckModel::applyFilter(const QString &filter)
{
    setFilter(filter);
}
