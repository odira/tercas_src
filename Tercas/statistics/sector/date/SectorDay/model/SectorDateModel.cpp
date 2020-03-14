#include <QDate>
#include <QSqlQuery>

#include "SectorDateModel.h"

#include <QDebug>

SectorDateModel::SectorDateModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    m_date = QDate::currentDate();
    m_date = m_date.addMonths(-1);

    m_sectors.clear();
    createSectorList();

    update();
}

void SectorDateModel::createSectorList()
{
    QString queryStr = QString("SELECT pid, label "
                               "FROM dblink('dbname=gis user=postgres', 'SELECT pid, label FROM fir.vw_sector WHERE compound is false AND pid != 28 AND pid != 29') "
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

void SectorDateModel::update()
{
    beginResetModel();
    generateRoleNames();
    QString queryStr = QString("SELECT * FROM statistics.f_get_sector_date_ct(%1, %2)")
            .arg(m_date.year())
            .arg(m_date.month());
    QSqlQuery query(queryStr);
    setQuery(query);
    endResetModel();
}

void SectorDateModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::UserRole + 1] = QVariant(QString("sectorPid").toUtf8()).toByteArray();
    for (int i = 1; i < ColumnsNumber; i++)
        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
}

QStringList SectorDateModel::roleNamesList() const
{
    QMap<int, QString> res;
    QHashIterator<int, QByteArray> i(m_roleNames);
    while (i.hasNext()) {
        i.next();
        if (i.key() > Qt::UserRole)
            res[i.key()] = i.value();
    }
    return res.values();
}

void SectorDateModel::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        update();
        emit dateChanged(m_date);
    }
}

int SectorDateModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_date.daysInMonth();
}

int SectorDateModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_sectors.length();
}

QVariant SectorDateModel::data(const QModelIndex &idx, int role) const
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
        case SectorDateModel_sector_pid: {
            int sectorPid = QSqlQueryModel::data(idx).toInt();
            for (int i = 0; i < m_sectors.length(); i++) {
                if (m_sectors.at(i)->pid == sectorPid)
                    return m_sectors.at(i)->label;
            }
            break;
        }
        default: {
            int vol = QSqlQueryModel::data(idx).toInt();
            return vol;
        }
        }
    }
    return QVariant();
}

QVariant SectorDateModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlQueryModel::headerData(section, orientation, role);
}

QVariant SectorDateModel::getSectorLabel(int row) const
{
    QModelIndex idx = createIndex(row, SectorDateModel_sector_pid);
    QString sectorLabel = data(idx, Qt::DisplayRole).toString();
    return sectorLabel;
}

QVariant SectorDateModel::getSectorLoad(int row, int day) const
{
    QModelIndex idx = createIndex(row, day);
    QString sectorVolume = data(idx, Qt::DisplayRole).toString();
    return sectorVolume;
}
