#pragma once

#include <QAbstractListModel>
#include <QDateTime>

QT_BEGIN_NAMESPACE
class QDateTime;
QT_END_NAMESPACE

class WatcherModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum WatcherRole {
        FullNameRole = Qt::UserRole + 1,
        SectorRole,
        SeatRole,
        StartTimeRole,
        NoteRole
    };
    Q_ENUM(WatcherRole)

    WatcherModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariantMap get(int row) const;
    Q_INVOKABLE void append(const QString &fullName,
                            const QString &sector,
                            const QString &seat,
                            const QDateTime &startTime,
                            const QString &note = QString());
    Q_INVOKABLE void set(int row,
                         const QString &fullName,
                         const QString &sector,
                         const QString  &seat,
                         const QDateTime &startTime,
                         const QString &note);
    Q_INVOKABLE void remove(int row);

private:
    struct Watcher {
        QString fullName;
        QString sector;
        QString seat;
        QDateTime startTime;
        QString note;
    };

    QList<Watcher> m_watchers;
};
