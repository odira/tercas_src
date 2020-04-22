#include <QtSql>

#include "TeamSheduleMonthModel.h"

TeamSheduleMonthModel::TeamSheduleMonthModel(QObject *parent, QSqlDatabase db):
    QSqlTableModel(parent, db)
{
    m_date = QDate::currentDate();
    m_date.setDate(m_date.year(), m_date.month(), 1);
    m_shiftnum = 4;

    setEditStrategy(QSqlTableModel::OnManualSubmit);

    update();
}

void TeamSheduleMonthModel::update()
{
    beginResetModel();
    getPersonPidArr();
    generateRoleNames();
    endResetModel();
}

void TeamSheduleMonthModel::getPersonPidArr()
{
    m_personPidArr.clear();
    QString queryString("SELECT pid "
                        "FROM person.vw_person "
                        "WHERE uservalid=true AND sectorspool='Пенза' AND shiftnum='Смена № 4' "
                        "ORDER BY surname");
    QSqlQuery query(queryString);
    while (query.next()) {
        int pid = query.value(0).toInt();
        m_personPidArr.append(pid);
    }
}

void TeamSheduleMonthModel::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        emit dateChanged(m_date);
        update();
    }
}

void TeamSheduleMonthModel::setShiftnum(const int &shiftnum)
{
    if (shiftnum != m_shiftnum) {
        m_shiftnum = shiftnum;
        emit shiftnumChanged(m_shiftnum);
        update();
    }
}

QVariant TeamSheduleMonthModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int row = idx.row();
    int col = idx.column();

    if (row < 0 || row > rowCount() || col < 0 || col > columnCount())
        return QVariant();

    // Calculate days in current month
    int daysInMonth = m_date.daysInMonth();

    // Calculate inner date for item
    QDate item_date(m_date.year(), m_date.month(), 1);
    if (col == 1 || col == 2 || col == 3)
        item_date = item_date.addDays(col - 4);
    else if (col > 3 && col < 3 + daysInMonth)
        item_date = QDate(m_date.year(), m_date.month(), col - 3);
    else
        item_date = QDate(m_date.year(), m_date.month(), daysInMonth).addDays(col - 3 - daysInMonth);

    // Calculate date opacity (out of month)
    bool out_of_month = (
                item_date.month() == m_date.month()
                ? true : false
    );
    if (col == 0)
        out_of_month = true;

    switch (role)
    {
    case Qt::DisplayRole:
        if (col == 0)
            return m_personPidArr.at(row);
        else
//            return item_date.toString("yyyy-MM-dd");
            return "OK";
        break;

    case Qt::BackgroundRole:
        if (col == 0)
            return true;
        return out_of_month;
        break;
    }

    if (role > Qt::UserRole)
    {
        switch (role - Qt::UserRole - 1) {
        case 0: // out_of_month
            return out_of_month;
            break;
        }
    }

    return QSqlTableModel::data(idx, role);
}

int TeamSheduleMonthModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_personPidArr.length();
}

int TeamSheduleMonthModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1 + 37;
}

void TeamSheduleMonthModel::generateRoleNames()
{
    m_roleNames.clear();

    m_roleNames[Qt::DisplayRole] = QVariant(QString("display").toUtf8()).toByteArray();
    m_roleNames[Qt::BackgroundRole] = QVariant(QString("background").toUtf8()).toByteArray();

    m_roleNames[Qt::UserRole + 1] = QVariant(QString("out_of_month").toUtf8()).toByteArray();

//    // First role is 'person' role
//    m_roleNames[Qt::UserRole + 1] = QVariant(QString("person").toUtf8()).toByteArray();

//    // Number of days role
//    int daysRoleCount = 37;
//    // Other roles is array counting from 1 to number of days
//    for (int i = 1; i <= daysRoleCount; i++)
//        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
}

QStringList TeamSheduleMonthModel::roleNamesList() const
{
    QMap<int, QString> res;
    QHashIterator<int, QByteArray> i(m_roleNames);
    while (i.hasNext()) {
        i.next();
        if (i.key() > Qt::UserRole) {
            res[i.key()] = i.value();
        }
    }
    return res.values();
}
