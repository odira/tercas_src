#include <QtSql>

#include "HolidayModel.h"

HolidayModel::HolidayModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLE);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    generateRoleNames();
    select();
}

void HolidayModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::DisplayRole] = QVariant(QString("display").toUtf8()).toByteArray();

    m_roleNames[Qt::UserRole + 1 + 0] = QVariant(QString("pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 1] = QVariant(QString("date").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 2] = QVariant(QString("type").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 3] = QVariant(QString("note_ru").toUtf8()).toByteArray();
}

//QStringList HolidayModel::roleNamesList() const
//{
//    QMap<int, QString> res;
//    QHashIterator<int, QByteArray> i(m_roleNames);
//    while (i.hasNext()) {
//        i.next();
//        if (i.key() > Qt::UserRole)
//            res[i.key()] = i.value();
//    }
//    return QStringList(res.values());
//}

QVariant HolidayModel::data(const QModelIndex &idx, int role) const
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
        if (col == Column_date)
            return QSqlTableModel::data(idx).toDate().toString("yyyy MMM dd");
        else
            return QSqlTableModel::data(idx);
    }
    else if (role > Qt::UserRole)
    {
        int colIndex = role - Qt::UserRole - 1;
        QModelIndex index = this->index(row, colIndex);
//        return QSqlTableModel::data(index, Qt::DisplayRole);
        return this->data(index, Qt::DisplayRole);
    }
    else {
        return QSqlTableModel::data(idx, role);
    }
}

bool HolidayModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (idx.isValid() && role == Qt::EditRole) {
        QSqlTableModel::setData(idx, value, role);
        emit dataChanged(idx, idx);
        return true;
    }
    return false;
}

bool HolidayModel::submitDB()
{
    return submitAll();
}

void HolidayModel::revertDB()
{
    revertAll();
}

QVariant HolidayModel::get(int row) const
{
    if (row < 0 || row >= rowCount())
        return QVariant();

    QMap<QString, QVariant> data;

    QHashIterator<int, QByteArray> iterator(roleNames());
    while (iterator.hasNext()) {
        iterator.next();
        data.insert(iterator.value(), this->data(index(row, iterator.key() - Qt::UserRole - 1), iterator.key()).toString());

    }
    return data;
}

bool HolidayModel::set(int row, QVariant value, QString role)
{
    if (row < 0 || row > rowCount())
        return false;

    QHashIterator<int, QByteArray> iterator(roleNames());
    while (iterator.hasNext()) {
        iterator.next();
        if (iterator.value() == role) {
            QModelIndex index = createIndex(row, iterator.key() - Qt::UserRole - 1);
            if (!index.isValid())
                return false;

            return setData(index, value, Qt::EditRole);
        }
    }

    return false;
}

bool HolidayModel::deleteRow(int row)
{
    return QSqlTableModel::removeRow(row);
}

void HolidayModel::add(QDate date, QString type, QString noteRu)
{
    QSqlRecord rec = record();
    rec.setValue("date", date);
    rec.setValue("type", type);
    rec.setValue("note_ru", noteRu);
    insertRecord(rowCount(), rec);
}
