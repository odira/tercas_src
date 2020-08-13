#include <QtSql>

#include "HolidayModel.h"

#include <QDebug>

HolidayModel::HolidayModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable(PGSQL_TABLE);
    setEditStrategy(QSqlTableModel::OnManualSubmit);

    update();
}

void HolidayModel::generateRoleNames()
{
    m_roleNames.clear();

    m_roleNames[PidRole]  = "pid";
    m_roleNames[DateRole] = "date";
    m_roleNames[TypeRole] = "type";
    m_roleNames[NoteRole] = "note";
}

void HolidayModel::update()
{
    generateRoleNames();
    select();
}

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
        if (col == DateRole) {
            QDate date = QSqlTableModel::data(idx).toDate();
            qDebug() << date;
            return date;
        } else if (col == TypeRole) {
            QString type = QSqlTableModel::data(idx).toString();
            return type;
        } else if (col == NoteRole) {
            QString note = QSqlTableModel::data(idx).toString();
            return note;
        } else
            return QSqlTableModel::data(idx);
    }
    else if (role > Qt::UserRole)
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex index = this->index(row, columnIdx);
        return this->data(index, Qt::DisplayRole);
    }

    return QVariant();
}

bool HolidayModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (idx.isValid() && role == Qt::EditRole) {
        QSqlTableModel::setData(idx, value, role);
        emit dataChanged(idx, idx);
        return true;
    } else if(role > Qt::UserRole) {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex index = this->index(idx.row(), columnIdx);
        return this->setData(index, value, Qt::EditRole);
    } else
        return false;
}

//void HolidayModel::save(int pid, QDate date, QString type, QString note)
//{
//    QSqlQuery query;
//    query.prepare("UPDATE calendar.vw_holiday SET date=:date, type=:type, note=:note WHERE pid=:pid");
//    query.bindValue(0, date);
//    query.bindValue(1, type);
//    query.bindValue(2, note);
//    query.bindValue(3, pid);
//    query.exec();

//    update();
//}

//#include <QDebug>
//void HolidayModel::add()
//{
//    beginInsertRows(QModelIndex(), 0, 0);
//    endInsertRows();

//    qDebug() << "ADD";
//}

//bool HolidayModel::submitDB()
//{
//    return submitAll();
//}

//void HolidayModel::revertDB()
//{
//    revertAll();
//}

//QVariant HolidayModel::get(int row) const
//{
//    if (row < 0 || row >= rowCount())
//        return QVariant();

//    QMap<QString, QVariant> data;

//    QHashIterator<int, QByteArray> iterator(roleNames());
//    while (iterator.hasNext()) {
//        iterator.next();
//        data.insert(iterator.value(), this->data(index(row, iterator.key() - Qt::UserRole - 1), iterator.key()).toString());

//    }
//    return data;
//}

//bool HolidayModel::set(int row, QVariant value, QString role)
//{
//    if (row < 0 || row > rowCount())
//        return false;

//    QHashIterator<int, QByteArray> iterator(roleNames());
//    while (iterator.hasNext()) {
//        iterator.next();
//        if (iterator.value() == role) {
//            QModelIndex index = createIndex(row, iterator.key() - Qt::UserRole - 1);
//            if (!index.isValid())
//                return false;

//            return setData(index, value, Qt::EditRole);
//        }
//    }

//    return false;
//}

//bool HolidayModel::deleteRow(int row)
//{
//    return QSqlTableModel::removeRow(row);
//}

//void HolidayModel::add(QDate date, QString type, QString noteRu)
//{
//    QSqlRecord rec = record();
//    rec.setValue("date", date);
//    rec.setValue("type", type);
//    rec.setValue("note_ru", noteRu);
//    insertRecord(rowCount(), rec);
//}
