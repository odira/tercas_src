#include <QDateTime>

#include "WatcherModel.h"

WatcherModel::WatcherModel(QObject *parent ) : QAbstractListModel(parent)
{
    m_watchers.append( { "Ильин", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20), QTime(05, 05, 05)), "Unknown" } );
    m_watchers.append( { "Лисяк", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20)), "Unknown" } );
    m_watchers.append( { "Маркелов", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20)), "Unknown" } );
    m_watchers.append( { "Степанов", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20)), "Unknown" } );
    m_watchers.append( { "Степанова", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20)), "Unknown" } );
    m_watchers.append( { "Платонова", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20)), "Unknown" } );
    m_watchers.append( { "Юреня", "П1", "РЛУ", QDateTime(QDate(2017, 10, 20)), "Unknown" } );
}

int WatcherModel::rowCount(const QModelIndex &) const
{
    return m_watchers.count();
}

QVariant WatcherModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount())
        switch (role) {
        case FullNameRole:
            return m_watchers.at(index.row()).fullName;
        case SectorRole:
            return m_watchers.at(index.row()).sector;
        case SeatRole:
            return m_watchers.at(index.row()).seat;
        case StartTimeRole:
            return m_watchers.at(index.row()).startTime;
        case NoteRole:
            return m_watchers.at(index.row()).note;
        default:
            return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> WatcherModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { FullNameRole, "fullName" },
        { SectorRole, "sector" },
        { SeatRole, "seat" },
        { StartTimeRole, "startTime"},
        { NoteRole, "note" }
    };
    return roles;
}

QVariantMap WatcherModel::get(int row) const
{
    const Watcher watcher = m_watchers.value(row);
    return { {"fullName", watcher.fullName}, {"sector", watcher.sector}, {"seat", watcher.seat}, {"startTime", watcher.startTime}, {"note", watcher.note} };
}

void WatcherModel::append(const QString &fullName, const QString &sector, const QString &seat, const QDateTime &startTime, const QString &note)
{
    int row = m_watchers.count();
    beginInsertRows(QModelIndex(), row, row);
    m_watchers.insert(row, {fullName, sector, seat, startTime, note});
    endInsertRows();
}

void WatcherModel::set(int row, const QString &fullName, const QString &sector, const QString &seat, const QDateTime &startTime, const QString &note)
{
    if (row < 0 || row >= m_watchers.count())
        return;

    m_watchers.replace(row, { fullName, sector, seat, startTime, note });
    dataChanged(index(row, 0), index(row, 0), { FullNameRole, SectorRole, SeatRole, StartTimeRole, NoteRole });
}

void WatcherModel::remove(int row)
{
    if (row < 0 || row >= m_watchers.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_watchers.removeAt(row);
    endRemoveRows();
}
