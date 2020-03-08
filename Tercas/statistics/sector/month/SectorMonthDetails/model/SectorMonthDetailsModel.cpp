#include <QSqlQuery>

#include "SectorMonthDetailsModel.h"

SectorMonthDetailsModel::SectorMonthDetailsModel(QObject *parent)
    : QSqlTableModel(parent)
{
    m_date = QDate::currentDate();
    m_date = m_date.addMonths(-1);

    m_sectors.clear();
    createSectorsList();

    generateRoleNames();
    update();
}

void SectorMonthDetailsModel::createSectorsList()
{
    QString queryStr = QString("SELECT pid, label "
                               "FROM dblink('dbname=gis user=postgres', "
                               "            'SELECT pid, label FROM fir.vw_sector WHERE compound is false AND pid != 28 AND pid != 29') "
                               "AS t (pid INTEGER, label TEXT)");
    QSqlQuery query(queryStr);
    while (query.next()) {
        int pid = query.value(0).toInt();
        QString label = query.value(1).toString();

        Sector *sector = new Sector();
        sector->pid = pid;
        sector->label = label;

        m_sectors.append(sector);
    }
}

void SectorMonthDetailsModel::update()
{
    beginResetModel();
    QString queryStr = QString("SELECT * FROM statistics.f_get_sector_month_details(%1, %2)")
            .arg(m_date.year()).arg(m_date.month());
    QSqlQuery query(queryStr);
    setQuery(query);
    endResetModel();
}

void SectorMonthDetailsModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::DisplayRole]  = QVariant(QString("display").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1] = QVariant(QString("sectorPid").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 2] = QVariant(QString("total").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 3] = QVariant(QString("max").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 4] = QVariant(QString("avg").toUtf8()).toByteArray();
}

int SectorMonthDetailsModel::rowCount(const QModelIndex &parent) const
{
    return QSqlTableModel::rowCount(parent);
}

int SectorMonthDetailsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

void SectorMonthDetailsModel::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        update();
        emit dateChanged(m_date);
    }
}

void SectorMonthDetailsModel::setYear(const int &year)
{
    int day = m_date.day();
    int month = m_date.month();
    this->setDate(QDate(year, month, day));
}

void SectorMonthDetailsModel::setMonth(const int &month)
{
    int day = m_date.day();
    int year = m_date.year();
    this->setDate(QDate(year, month, day));
}

QVariant SectorMonthDetailsModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    int row = idx.row();

    if (col < 0 || col > columnCount())
        return QVariant();

    if (row < 0 || row > rowCount())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (col) {
        case SectorMonthDetailsModel_sector_pid: {
            int sectorPid = QSqlQueryModel::data(idx).toInt();
            for (int i = 0; i < m_sectors.length(); i++) {
                if (m_sectors.at(i)->pid == sectorPid)
                    return m_sectors.at(i)->label;
            }
            break;
        }
        default: {
            int vol = QSqlTableModel::data(idx).toInt();
            return vol;
        }
        }
    }
    else if (role > Qt::UserRole)
    {
        if (m_roleNames[role] == "sectorPid") {
            return data(idx, Qt::DisplayRole);
        }
        else {
            int col = role - Qt::UserRole - 1;
            int vol = QSqlQueryModel::data(createIndex(row, col), Qt::DisplayRole).toInt();
            return vol;
        }
    }

    return QVariant();
}

QVariant SectorMonthDetailsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlQueryModel::headerData(section, orientation, role);
}

QVariant SectorMonthDetailsModel::getSectorLabel(int row) const
{
    QModelIndex idx = createIndex(row, SectorMonthDetailsModel_sector_pid);
    QString sectorLabel = data(idx, Qt::DisplayRole).toString();
    return sectorLabel;
}

QVariant SectorMonthDetailsModel::getSectorLoad(int row, int day) const
{
    QModelIndex idx = createIndex(row, day);
    QString sectorVolume = data(idx, Qt::DisplayRole).toString();
    return sectorVolume;
}
