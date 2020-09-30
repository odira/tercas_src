#include <QtSql>
#include <QDate>
#include <QMap>
#include <QString>
#include <QLocale>

#include "EmplSheduleMonthModel.h"

EmplSheduleMonthModel::EmplSheduleMonthModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    m_date = QDate::currentDate();
    m_shiftnum = 4;

    // Initialize the person pids array
    m_personPidArray.clear();
    QString queryString("SELECT pid "
                        "FROM person.vw_person "
                        "WHERE valid=true AND sectors_pool='Пенза' AND shift_num=4 ");
//                        "ORDER BY surname");
    QSqlQuery query(queryString);
    while (query.next()) {
        int pid = query.value(0).toInt();
        m_personPidArray.append(pid);
    }

    setEditStrategy(QSqlTableModel::OnManualSubmit);
    update();
}

void EmplSheduleMonthModel::generateRoleNames()
{
    // Calculate number of days in month
    int daysRoleCount = m_date.daysInMonth();

    m_roleNames.clear();
    // First role is 'person' role
    m_roleNames[Qt::UserRole + 1] = QVariant(QString("person").toUtf8()).toByteArray();
    // Other roles is array counting from 1 to number of days in month
    for (int i = 1; i <= daysRoleCount; i++) {
        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
    }
}

QStringList EmplSheduleMonthModel::roleNamesList() const
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

void EmplSheduleMonthModel::update()
{
    beginResetModel();
    generateRoleNames();
//    layoutChanged();
    endResetModel();
}

QVariant EmplSheduleMonthModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int row = idx.row();
    int col = idx.column();

    if (col < 0 || col > columnCount())
        return QVariant();

    if (row < 0 || row > rowCount())
        return QVariant();

    if (role < Qt::UserRole)
    {

        if (row < m_personPidArray.length())
        {
            switch (role)
            {
            case Qt::DisplayRole:
            {
                QString abbr = QString();

                int personPid = m_personPidArray.at(row);
                QDate date = QDate(m_date.year(), m_date.month(), col + 1);
                QString queryString = QString("SELECT activity_abbr FROM calendar.vw_empl_period "
                                              "WHERE person_pid='%1' AND '%2' BETWEEN start_date AND end_date")
                        .arg(personPid)
                        .arg(date.toString("yyyy-MM-dd"));
                QSqlQuery query(queryString);
                while (query.next()) {
                    abbr = query.value(0).toString();
                    return abbr;
                }

                queryString.clear();
                query.clear();

                return QVariant();
                // break;

            } // Qt::DisplayRole

            case Qt::ToolTipRole:
            {
                int personPid = m_personPidArray.at(row);
                QDate date = QDate(m_date.year(), m_date.month(), col + 1);
                QString queryStr = QString("SELECT emplshedulenoteru FROM calendar.f_get_emplactivity(%1, '%2')")
                        .arg(personPid)
                        .arg(date.toString("yyyy-MM-dd"));
                QSqlQuery query(queryStr);
                while (query.next()) {
                    QString emplshedulenoteru = query.value(0).toString();
                    return emplshedulenoteru;
                }

                break;
            } // Qt::ToolTipRole

            case Qt::TextAlignmentRole:
            {

                return Qt::AlignCenter;
                // break;

            } // Qt::TextAlignmentRole

            case Qt::ForegroundRole:
            {
                return QBrush(QColor("black"));
                // break;
            } // Qt::ForegroundRole

            } // switch (role)
        }
    }
    else if (role > Qt::UserRole)
    {
        int personPid = m_personPidArray.at(row);

        int col = role - Qt::UserRole - 1;
        if (col == 0) // person role
        {
            QString queryString = QString("SELECT (surname || ' ' || left(name, 1) || '.' || left(middlename, 1) || '.') AS fullname "
                                          "FROM person.vw_person "
                                          "WHERE pid=%1")
                    .arg(personPid);
            QSqlQuery query(queryString);
            while (query.next()) {
                QString fullname = query.value(0).toString();
                return fullname;
            }
        }
        else // dayOfMonth role
        {
            QDate date = QDate(m_date.year(), m_date.month(), col - 1);
            QString queryStr = QString("SELECT pid FROM calendar.vw_empl_period WHERE person_pid='%1' AND '%2' BETWEEN start_date AND end_date")
                    .arg(personPid)
                    .arg(date.toString("yyyy-MM-dd"));
            QSqlQuery query(queryStr);
            while (query.next()) {
                QString pid = query.value(0).toString();
                return pid;
            }
        }
    }

    return QSqlTableModel::data(idx, role);
}

QVariant EmplSheduleMonthModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section < 0 || section >= columnCount()) {
            return QVariant();
        }

        switch (role)
        {

        case Qt::DisplayRole:
            QDate date(m_date.year(), m_date.month(), section + 1);
            QLocale ruLocale(QLocale::Russian);
            QString headerString = ruLocale.toString(date, QString("ddd")) + "\n" + QString::number(section + 1);
            return headerString;

        } // switch
    }
    else if (orientation == Qt::Vertical)
    {
        if (section < 0 || section >= rowCount()) {
            return QVariant();
        }

        switch (role)
        {

        case Qt::DisplayRole:
        {
            if (section < rowCount())
            {
                if (section < m_personPidArray.length())
                {
                    int personPid = m_personPidArray.at(section);
                    QString queryString = QString("SELECT (surname || ' ' || left(name, 1) || '. ' || left(middlename, 1) || '.') AS fullname "
                                                  "FROM person.vw_person "
                                                  "WHERE pid=%1")
                            .arg(personPid);
                    QSqlQuery query(queryString);
                    while (query.next()) {
                        QString fullname = query.value(0).toString();
                        return fullname;
                    }
                }
                else if (section == m_personPidArray.length()) // String to show person count
                {
                    return QString(tr("Всего: %1")
                                   .arg(m_personPidArray.length()));
                }
                else {
                    return QVariant();
                }
            }
        } // Qt::DisplayRole

        case Qt::TextAlignmentRole:
        {
            if (section < m_personPidArray.length()) {
                return Qt::AlignRight;
            } else if (section == m_personPidArray.length()) {
                return Qt::AlignCenter;
            } else {
                return QVariant();
            }
             // break;
        } // Qt::TextAlignmentRole

        case Qt::FontRole:
        {
            QFont font("Helvetica", 12);
                    if (section < m_personPidArray.size())
                    font.setBold(true);
                    else
                    font.setBold(false);
                    return font;
            // break;
        } // Qt::FontRole

        } // switch
    }

    return QSqlTableModel::headerData(section, orientation, role);
}

int EmplSheduleMonthModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_personPidArray.length();
}

int EmplSheduleMonthModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_date.daysInMonth() + 1; // days in month + column 'person'
}

QVariant EmplSheduleMonthModel::getPersonPid(int row) const
{
    return m_personPidArray.at(row);
}

QVariant EmplSheduleMonthModel::get(int personpid, int day) const
{
    QDate date = QDate(m_date.year(), m_date.month(), day);
    QString queryStr = QString("SELECT activity_abbr FROM calendar.vw_empl_period "
                               "WHERE person_pid='%1' AND '%2' BETWEEN start_date AND end_date")
            .arg(personpid)
            .arg(date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString emplactivityabbr = query.value(0).toString();
        return emplactivityabbr;
    }

    queryStr.clear();
    query.clear();
    queryStr = QString("SELECT entactivityabbr FROM calendar.vw_entshedule "
                       "WHERE date='%1'")
            .arg(date.toString("yyyy-MM-dd"));
    query.exec(queryStr);
    while (query.next()) {
        QString entabbr = query.value(0).toString();
        return entabbr;
    }

    return  QVariant();
}

bool EmplSheduleMonthModel::isHoliday(QDate date) const
{
    date = date.addDays(1);
    bool isholiday = false;
    QString queryStr = QString("SELECT calendar.f_isholiday('%1')")
            .arg(date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    while (query.next()) {
        isholiday = query.value(0).toBool();
    }
    return isholiday;
}

bool EmplSheduleMonthModel::isDayOff(QDate date) const
{
    date = date.addDays(1);
    bool isdayoff = false;

    if (date.dayOfWeek() == 6 || date.dayOfWeek() == 7)
        isdayoff = true;

    QString queryStr = QString("SELECT calendar.f_isdayoff('%1')")
            .arg(date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    while (query.next()) {
        bool check = query.value(0).toBool();
        if (check) isdayoff = true;
    }

    queryStr = QString("SELECT calendar.f_isworkingday('%1')")
            .arg(date.toString("yyyy-MM-dd"));
    query.clear();
    query = QSqlQuery(queryStr);
    while (query.next()) {
        bool check = query.value(0).toBool();
        if (check) isdayoff = false;
    }

    return isdayoff;
}

QVariant EmplSheduleMonthModel::getColor(int row, int column) const
{
    if (row < 0 || row > rowCount())
        return QVariant();

    int personpid = m_personPidArray.at(row);
    QDate date = QDate(m_date.year(), m_date.month(), column);

    QString queryStr = QString("SELECT activity_color "
                               "FROM calendar.vw_empl_period "
                               "WHERE person_pid='%1' AND '%2' BETWEEN start_date AND end_date")
            .arg(personpid)
            .arg(date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString emplcolor = query.value(0).toString();
        return emplcolor;
    }

    queryStr.clear();
    query.clear();

    queryStr = QString("SELECT entactivitycolor FROM calendar.vw_entshedule "
                       "WHERE date='%1'")
            .arg(date.toString("yyyy-MM-dd"));
    query.exec(queryStr);
    while (query.next()) {
        QString entcolor = query.value(0).toString();
        return entcolor;
    }

    return QVariant();
}

#include <QDebug>
QVariant EmplSheduleMonthModel::getAbbr(int personpid, int day) const
{
    QDate date = QDate(m_date.year(), m_date.month(), day);
    QString queryStr = QString("SELECT activity_abbr FROM calendar.vw_empl_period "
                               "WHERE person_pid='%1' AND '%2' BETWEEN start_date AND end_date")
            .arg(personpid)
            .arg(date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString emplactivityabbr = query.value(0).toString();
        return emplactivityabbr;
    }

    queryStr.clear();
    query.clear();
    queryStr = QString("SELECT activityabbr FROM calendar.vw_ent_shedule "
                       "WHERE date='%1'")
            .arg(date.toString("yyyy-MM-dd"));
    query.exec(queryStr);
    while (query.next()) {
        QString entabbr = query.value(0).toString();
        return entabbr;
    }

    return QVariant();
}

QVariant EmplSheduleMonthModel::getToolTip(int personpid, int day) const
{
    QDate date = QDate(m_date.year(), m_date.month(), day);

    QString queryStr = QString("SELECT activity_note FROM calendar.vw_empl_period "
                               "WHERE person_pid='%1' AND '%2' BETWEEN start_date AND end_date")
                               .arg(personpid)
                               .arg(date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    while(query.next()) {
        QString activity_note = query.value(0).toString();
        QString tooltip = activity_note;
        return tooltip;
    }

    return QVariant();
}

QVariant EmplSheduleMonthModel::getNumberAvailable(int day) const
{
    int num = 0;
    int personNum = m_personPidArray.length();
    for (int i = 0; i < personNum; i++) {
        if (!data(createIndex(i, day)).toString().isEmpty())
            num++;
    }
    return personNum - num;
}

void EmplSheduleMonthModel::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        m_date.setDate(m_date.year(), m_date.month(), m_date.day());
        emit dateChanged(m_date);
        update();
    }
}

void EmplSheduleMonthModel::setShiftnum(const int &shiftnum)
{
    if (shiftnum != m_shiftnum) {
        m_shiftnum = shiftnum;
        emit shiftnumChanged();
        update();
    }
}

void EmplSheduleMonthModel::setSectorspool(const int &sectorspool)
{
    if (sectorspool != m_sectorspool) {
        m_sectorspool = sectorspool;
        emit sectorspoolChanged();
        update();
    }
}
