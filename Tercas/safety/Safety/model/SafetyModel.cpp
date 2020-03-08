#include <QSqlQuery>
#include <QDateTime>

#include "SafetyModel.h"

SafetyModel::SafetyModel(QObject *parent)
    : QSqlTableModel(parent)
{
    generateRoleNames();
    update();
}

void SafetyModel::generateRoleNames()
{
    m_roleNames.clear();

    m_roleNames[Qt::DisplayRole]    = QVariant(QString("display").toUtf8()).toByteArray();
    m_roleNames[Qt::ForegroundRole] = QVariant(QString("foreground").toUtf8()).toByteArray();
    m_roleNames[Qt::BackgroundRole] = QVariant(QString("background").toUtf8()).toByteArray();

    for (int i = 0; i < ColumnsNumber; i++) {
        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString(QString("_") + QString::number(i)).toUtf8()).toByteArray();
    }
}

void SafetyModel::update()
{
    beginResetModel();
    QString queryStr = QString("SELECT * FROM safety.vw_safety");
    QSqlQuery query(queryStr);
    setQuery(query);
    endResetModel();
}

int SafetyModel::rowCount(const QModelIndex &parent) const
{
    return QSqlTableModel::rowCount(parent);
}

int SafetyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsNumber;
}

QVariant SafetyModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    int row = idx.row();

    if (col < 0 || col > columnCount())
        return QVariant();
    else if (row < 0 || row > rowCount())
        return QVariant();

    if (role > Qt::UserRole) {
        int newCol = role - Qt::UserRole - 1;
        QModelIndex newIdx = createIndex(row, newCol);
        return this->data(newIdx, Qt::DisplayRole);
    }

    if (col == SafetyModel_ts)
    {
        switch (role) {
        case Qt::DisplayRole: {
            QDateTime ts = QSqlTableModel::data(idx, role).toDateTime();
            return QString("<b>" + ts.toString("yyyy") + "</b>" +
                           "<font color='blue'>" + ts.toString(" MMMM ") + "</font>" +
                           "<font color='green'><b>" + ts.toString("d") + "</b></font>");
            // break;
        }
        default:
            return QSqlTableModel::data(idx, role);
            // break;
        }
    }
    else
    {
        switch (role)
        {
        case Qt::DisplayRole: {
            return QSqlTableModel::data(idx).toString();
            // break;
        }
        default:
            return QSqlTableModel::data(idx, role);
            // break;
        }
    }

//    SafetyModel_acc,
//    SafetyModel_department,
//    SafetyModel_shift,
//    SafetyModel_sector,
//    SafetyModel_sectorlabel,
//    SafetyModel_sectorcolor,
//    SafetyModel_node_pid,
//    SafetyModel_classification,
//    SafetyModel_type,
//    SafetyModel_note,
//    SafetyModel_spospid,
//    SafetyModel_spos,
//    SafetyModel_tcas1,
//    SafetyModel_tcas2,
//    ColumnsNumber

//        }
//    }




//    if (role == Qt::DisplayRole)
//    {
//        switch (col)
//        {

//        // Zero'es column
//        case SafetyModel_sector_pid:
//        {
//            if (row == (rowCount() - 1))
//                return tr("Всего");
//            else {
//                int sectorPid = QSqlQueryModel::data(idx).toInt();
//                for (int i = 0; i < m_sectors.length(); i++) {
//                    if (m_sectors.at(i)->pid == sectorPid)
//                        return m_sectors.at(i)->label;
//                }
//            }

//            break;
//        }

//        // Last column
//        case SafetyModel_sector_total:
//        {
//            // Total number of the year
//            if (row == (rowCount() - 1)) {
//                QString queryStr = QString("SELECT sum(load) "
//                                           "FROM statistics.sector_date "
//                                           "WHERE date_part('year', date)=%1")
//                        .arg(m_date.year());
//                QSqlQuery query(queryStr);
//                while (query.next()) {
//                    int totalYear = query.value(0).toInt();
//                    return totalYear;
//                }
//            }
//            else {
//                int pid = QSqlQueryModel::data(createIndex(row, SafetyModel_sector_pid), role).toInt();
//                for (int i = 0; i < m_sectors.length(); i++)
//                    if (m_sectors.at(i)->pid == pid) {
//                        QString queryStr = QString("SELECT sum(load) "
//                                                   "FROM statistics.sector_date "
//                                                   "WHERE sector_pid=%1 AND date_part('year', date)=%2")
//                                .arg(pid)
//                                .arg(m_date.year());
//                        QSqlQuery query(queryStr);
//                        while (query.next()) {
//                            int sectorYear = query.value(0).toInt();
//                            return sectorYear;
//                        }
//                    }
//            }

//            break;
//        }

//        // Other columns
//        default:
//        {
//            // Last row (month total result)
//            if (row == (rowCount() - 1)) {
//                QString queryStr = QString("SELECT sum(load) "
//                                           "FROM statistics.sector_date "
//                                           "WHERE date_part('year', date)=%1 AND date_part('month', date)=%2")
//                        .arg(m_date.year())
//                        .arg(col);
//                QSqlQuery query(queryStr);
//                while (query.next()) {
//                    int sectorYearMonth = query.value(0).toInt();
//                    return sectorYearMonth;
//                }
//            }
//            else {
//                int vol = QSqlTableModel::data(idx).toInt();
//                return vol;
//            }

//            break;
//        }

//        } // switch
//    }

    return QVariant();
}

QVariant SafetyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlQueryModel::headerData(section, orientation, role);
}
