#include <QSqlQuery>

#include "SectorMonthModel.h"

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
                               "FROM dblink('dbname=gis user=postgres', "
                               "            'SELECT pid, label, color FROM fir.vw_sector WHERE compound is false AND pid != 28 AND pid != 29') "
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

    // First role name is 'sectorPid'
    m_roleNames[Qt::UserRole + 1] = QVariant(QString("sectorPid").toUtf8()).toByteArray();
    // Next role names are numbers from '1' to '12'
    for (int i = 1; i < SectorMonthModel_sector_pid; i++)
        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
    // Role name 'sectorTotal'
    m_roleNames[Qt::UserRole + 1 + SectorMonthModel_sector_total] = QVariant(QString("sectorTotal").toUtf8()).toByteArray();
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
    return QSqlTableModel::rowCount(parent) + 1;
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
        switch (col)
        {

        // Zero'es column
        case SectorMonthModel_sector_pid:
        {
            if (row == (rowCount() - 1))
                return tr("Всего");
            else {
                int sectorPid = QSqlQueryModel::data(idx).toInt();
                for (int i = 0; i < m_sectors.length(); i++) {
                    if (m_sectors.at(i)->pid == sectorPid)
                        return m_sectors.at(i)->label;
                }
            }

            break;
        }

        // Last column
        case SectorMonthModel_sector_total:
        {
            // Total number of the year
            if (row == (rowCount() - 1)) {
                QString queryStr = QString("SELECT sum(load) "
                                           "FROM statistics.sector_date "
                                           "WHERE date_part('year', date)=%1")
                        .arg(m_date.year());
                QSqlQuery query(queryStr);
                while (query.next()) {
                    int totalYear = query.value(0).toInt();
                    return totalYear;
                }
            }
            else {
                int pid = QSqlQueryModel::data(createIndex(row, SectorMonthModel_sector_pid), role).toInt();
                for (int i = 0; i < m_sectors.length(); i++)
                    if (m_sectors.at(i)->pid == pid) {
                        QString queryStr = QString("SELECT sum(load) "
                                                   "FROM statistics.sector_date "
                                                   "WHERE sector_pid=%1 AND date_part('year', date)=%2")
                                .arg(pid)
                                .arg(m_date.year());
                        QSqlQuery query(queryStr);
                        while (query.next()) {
                            int sectorYear = query.value(0).toInt();
                            return sectorYear;
                        }
                    }
            }

            break;
        }

        // Other columns
        default:
        {
            // Last row (month total result)
            if (row == (rowCount() - 1)) {
                QString queryStr = QString("SELECT sum(load) "
                                           "FROM statistics.sector_date "
                                           "WHERE date_part('year', date)=%1 AND date_part('month', date)=%2")
                        .arg(m_date.year())
                        .arg(col);
                QSqlQuery query(queryStr);
                while (query.next()) {
                    int sectorYearMonth = query.value(0).toInt();
                    return sectorYearMonth;
                }
            }
            else {
                int vol = QSqlTableModel::data(idx).toInt();
                return vol;
            }

            break;
        }

        } // switch
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
