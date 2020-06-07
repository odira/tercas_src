#include <QtSql>

#include "PersonModel.h"

PersonModel::PersonModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable("person.vw_person");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    generateRoleNames();
    setFilter("valid IS true");
    select();
}

void PersonModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::DisplayRole] = QVariant(QString("display").toUtf8()).toByteArray();

    m_roleNames[Qt::UserRole + 1 + 0]  = QVariant(QString("pid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 1]  = QVariant(QString("valid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 2]  = QVariant(QString("surname").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 3]  = QVariant(QString("name").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 4]  = QVariant(QString("middlename").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 5]  = QVariant(QString("birthday").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 6]  = QVariant(QString("mobile_phone").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 7]  = QVariant(QString("tab_num").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 8]  = QVariant(QString("position").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 9]  = QVariant(QString("class").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 10] = QVariant(QString("shift_num").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 11] = QVariant(QString("sectors_pool").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 12] = QVariant(QString("service_period").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 13] = QVariant(QString("admission").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 14] = QVariant(QString("note").toUtf8()).toByteArray();
}

//QStringList PersonModel::roleNamesList() const
//{
//    QMap<int, QString> res;
//    QHashIterator<int, QByteArray> i(m_roleNames);
//    while (i.hasNext()) {
//        i.next();
//        if (i.key() > Qt::UserRole)
//            res[i.key()] = i.value();
//    }
//    return res.values();
//}

QVariant PersonModel::data(const QModelIndex &idx, int role) const
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
        if (col == Columns::person_birthday)
            return QSqlTableModel::data(idx).toDate().toString("yyyy MMM dd");
        else
            return QSqlTableModel::data(idx);
    }
    else if (role > Qt::UserRole)
    {
        int colIndex = role - Qt::UserRole - 1;
        QModelIndex index = this->index(row, colIndex);
        return QSqlTableModel::data(index, Qt::DisplayRole);
    }
    else {
        return QSqlTableModel::data(idx, role);
    }
}

bool PersonModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (idx.isValid() && role == Qt::EditRole) {
        QSqlTableModel::setData(idx, value, role);
        emit dataChanged(idx, idx);
        return true;
    }
    return false;
}

//bool PersonModel::submitDB()
//{
//    return submitAll();
//}

//void PersonModel::revertDB()
//{
//    revertAll();
//}

//QVariant PersonModel::get(int row) const
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

//bool PersonModel::set(int row, QVariant value, QString role)
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

//bool PersonModel::deleteRow(int row)
//{
//    return QSqlTableModel::removeRow(row);
//}

//void PersonModel::add(QDate date, QString type, QString noteRu)
//{
//    QSqlRecord rec = record();
//    rec.setValue("date", date);
//    rec.setValue("type", type);
//    rec.setValue("note_ru", noteRu);
//    insertRecord(rowCount(), rec);
//}
