#include <QtSql>
#include <QDate>

#include "HourSectorModel.h"

#include <QDebug>
HourSectorModel::HourSectorModel(QObject *parent)
    :  QSqlQueryModel(parent)
{
    m_date = QDate(2020, 1, 1);
//    m_date = QDate::currentDate();
//    qDebug() << m_date;
//    m_date.setDate(m_date.year(), m_date.month() - 2, m_date.day());
//    m_date.setDate(2019, 9, 1);
    createSectorList();
    update();
}

HourSectorModel::HourSectorModel(QDate date, QObject *parent)
    : QSqlQueryModel(parent), m_date(date)
{
    createSectorList();
    update();
}

void HourSectorModel::createSectorList()
{
    QString queryStr = QString("SELECT pid,label,npsdz,npspdz FROM "
                               "dblink('dbname=gis user=postgres','SELECT pid,label,npsdz,npspdz FROM fir.sector') "
                               "AS t1(pid INTEGER, label TEXT, npsdz INTEGER, npspdz INTEGER)");
    QSqlQuery query(queryStr);
    while (query.next()) {
        int pid = query.value(0).toInt();
        QString label = query.value(1).toString();
        int npsdz = query.value(2).toInt();
        int npspdz = query.value(3).toInt();

        Sector *sector = new Sector();
        sector->pid = pid;
        sector->label = label;
        sector->npsdz = npsdz;
        sector->npspdz = npspdz;

        m_sectors.append(sector);
    }
}

void HourSectorModel::update()
{
    beginResetModel();
    generateRoleNames();
    QString queryStr = QString("SELECT * FROM statistics.f_get_sector_hour_ct('%1')")
            .arg(m_date.toString("yyyy-MM-dd"));
    QSqlQuery query(queryStr);
    setQuery(query);
    endResetModel();
}

void HourSectorModel::generateRoleNames()
{
    m_roleNames.clear();
    m_roleNames[Qt::UserRole + 1] = QVariant(QString("sectorPid").toUtf8()).toByteArray();
    for (int i = 1; i < ColumnsNumber; i++)
        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
}

QStringList HourSectorModel::roleNamesList() const
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

void HourSectorModel::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        update();
        emit dateChanged(m_date);
    }
}

QVariant HourSectorModel::data(const QModelIndex &idx, int role) const
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
        if (col == hoursector_sector_pid) {
            int sectorPid = QSqlQueryModel::data(idx).toInt();
            for (int i = 0; i < m_sectors.length(); i++) {
                if (m_sectors.at(i)->pid == sectorPid)
                    return m_sectors.at(i)->label;
            }
        } else {
            int vol = QSqlQueryModel::data(idx).toInt();
            if (vol == 0) return QVariant();
            else return vol;
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        switch (col) {
        case hoursector_sector_pid:
            return  Qt::AlignCenter;
        default:
            return Qt::AlignCenter;
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        switch (col) {

        case hoursector_sector_pid:
            return QColor("yellow").name();

        default: {
            int vol = QSqlQueryModel::data(idx).toInt();
            if (vol == 0)
                return QColor("white").name();

            QModelIndex sectorIdx = createIndex(row, hoursector_sector_pid);
            int sectorPid = QSqlQueryModel::data(sectorIdx).toInt();
            for (int i = 0; i < m_sectors.length(); i++) {
                if (m_sectors.at(i)->pid == sectorPid) {
                    int npspdz = m_sectors.at(i)->npspdz;
                    int npsdz = m_sectors.at(i)->npsdz;

                    if (npsdz == 0 && npspdz == 0)
                        return QColor("#F3E96B").name();
                    else if (vol >= npspdz)
                        return QColor("#F22F08").name();
                    else if (vol >= npsdz)
                        return QColor("#F49F05").name();
                    else
                        return QColor("#99BFAA").name();
                }
            }
        }
        } // switch (col)
    }
    else if (role == Qt::ForegroundRole)
    {
        switch (col) {
        case hoursector_sector_pid:
            return QColor("blue");
        }
    }
    if (role > Qt::UserRole)
    {
        if (m_roleNames[role] == "sectorPid") {
            return data(idx, Qt::DisplayRole);
        }
        else { // hour role -- as digit
            int col = role - Qt::UserRole - 1;
            int vol = QSqlQueryModel::data(createIndex(row, col), Qt::DisplayRole).toInt();
            return vol;
        }
    }

    return QSqlQueryModel::data(idx, role);
}

QVariant HourSectorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section < 0 || section > ColumnsNumber)
            return QVariant();

        switch (role) {

        case Qt::DisplayRole:
            if (section == 0)
                return QString(tr("Сектор"));
            else {
                QString headerStr = QSqlQueryModel::headerData(section, orientation).toString();
                int header = headerStr.toInt();
                return QString("%1.00\n-\n%2.00").arg(header).arg(header + 1);
            }

        case Qt::FontRole: {
            QFont font;
            font.setBold(true);
            return font;
        }

        case Qt::ForegroundRole:
            return QColor(Qt::blue);

        } // switch (role)
    }
    else if (orientation == Qt::Vertical)
    {
        switch (role) {

        case Qt::ForegroundRole:
            return QColor(Qt::red);

        } // switch (role)
    }

    return QSqlQueryModel::headerData(section, orientation, role);
}

QVariant HourSectorModel::getSectorLabel(int rowNum) const
{
    QModelIndex idx = createIndex(rowNum, hoursector_sector_pid);
    QString sectorLabel = this->data(idx, Qt::DisplayRole).toString();
    return sectorLabel;
}

QVariant HourSectorModel::getSectorValue(int rowNum, int hour) const
{
    QModelIndex idx = createIndex(rowNum, hour);
    int sectorValue = QSqlQueryModel::data(idx, Qt::DisplayRole).toInt();
    return (sectorValue == 0) ? QVariant() : sectorValue;
}

#include <QDebug>
QVariant HourSectorModel::getSectorColor(int rowNum, int hour) const
{
    QModelIndex idx = createIndex(rowNum, hour);
    QString sectorColor = this->data(idx, Qt::BackgroundRole).toString();
    return sectorColor;
}
