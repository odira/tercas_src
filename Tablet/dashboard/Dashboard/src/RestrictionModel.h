#pragma once

#include <QAbstractListModel>

class RestrictionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RestrictionRole {
        AdRole = Qt::UserRole + 1,
        IndxMilRole,
        CallSignRole,
        ZoneRole,
        LevelFromRole,
        LevelToRole,
        TimeFromRole,
        TimeToRole,
        NoteRole
    };
    Q_ENUM(RestrictionRole)

    RestrictionModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariantMap get(int row) const;
    Q_INVOKABLE void append(const QString &ad,
                            const QString &indxMil,
                            const QString &callSign,
                            const QString &zone,
                            const QString &levelFrom,
                            const QString &levelTo,
                            const QString &timeFrom,
                            const QString &timeTo,
                            const QString &note);
    Q_INVOKABLE void set(int row,
                         const QString &ad,
                         const QString &indxMil,
                         const QString &callSign,
                         const QString &zone,
                         const QString &levelFrom,
                         const QString &levelTo,
                         const QString &timeFrom,
                         const QString &timeTo,
                         const QString &note);
    Q_INVOKABLE void remove(int row);

private:
    struct Restriction {
        QString ad;
        QString indxMil;
        QString callSign;
        QString zone;
        QString levelFrom;
        QString levelTo;
        QString timeFrom;
        QString timeTo;
        QString note;
    };

    QList<Restriction> m_restrictions;
};
