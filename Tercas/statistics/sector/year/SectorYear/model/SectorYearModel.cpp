#include <QSqlQuery>

#include "SectorYearModel.h"

#include <QDebug>
SectorMonthModel::SectorMonthModel(QObject *parent)
    : QSqlTableModel(parent)
{
    m_date = QDate::currentDate();
    m_date.setDate(2018, 1, 1);

    m_sectors.clear();
    createSectorsList();

    generateRoleNames();
    update();
}

void SectorMonthModel::createSectorsList()
{
    QString queryStr = QString("SELECT pid, label, color "
                               "FROM dblink('dbname=gis user=postgres', 'SELECT pid, label, color FROM fir.vw_sector WHERE compound is false AND pid != 28 AND pid != 29') "
                               "AS t (pid INTEGER, label TEXT, color TEXT)");
    QSqlQuery query(queryStr);
    while (query.next()) {
        int pid = query.value(0).toInt();
        QString label = query.value(1).toString();
        QString color = query.value(2).toString();

        Sector *sector = new Sector();
        sector->pid = pid;
        sector->label = label;
        sector->color = color;

        m_sectors.append(sector);
    }
}

void SectorMonthModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::UserRole + 1] = QVariant(QString("sectorPid").toUtf8()).toByteArray();
    for (int i = 1; i < ColumnsNumber; i++)
        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
}

void SectorMonthModel::update()
{
    beginResetModel();
    QString queryStr = QString("SELECT * FROM statistics.f_get_sector_month_ct(%1)")
            .arg(m_date.year());
    QSqlQuery query(queryStr);
    setQuery(query);
    endResetModel();
}

int SectorMonthModel::rowCount(const QModelIndex &parent) const
{
    return QSqlTableModel::rowCount(parent);
}

int SectorMonthModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsNumber;
}

void SectorMonthModel::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        update();
        emit dateChanged(m_date);
    }
}

//void SectorMonthModel::setYear(const int &year)
//{
//    int day = m_date.day();
//    int month = m_date.month();
//    this->setDate(QDate(year, month, day));
//}

QVariant SectorMonthModel::data(const QModelIndex &idx, int role) const
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
        case SectorMonthModel_sector_pid: {
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

QVariant SectorMonthModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlQueryModel::headerData(section, orientation, role);
}

QVariant SectorMonthModel::getSectorLabel(int row) const
{
    QModelIndex idx = createIndex(row, SectorMonthModel_sector_pid);
    QString sectorLabel = data(idx, Qt::DisplayRole).toString();
    return sectorLabel;
}

QVariant SectorMonthModel::getSectorLoad(int row, int day) const
{
    QModelIndex idx = createIndex(row, day);
    QString sectorVolume = data(idx, Qt::DisplayRole).toString();
    return sectorVolume;
}

QVariant SectorMonthModel::getSectorColor(int row) const
{
    return m_sectors.at(row)->color;
}
