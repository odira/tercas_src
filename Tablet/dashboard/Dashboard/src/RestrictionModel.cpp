#include "RestrictionModel.h"

RestrictionModel::RestrictionModel(QObject *parent ) : QAbstractListModel(parent)
{
    m_restrictions.append( { "Липецк-2", "ЬУВЛ", "Ворсовка", "UUR300", "GND", "350", "14.00", "15.00" , "Парашютные прыжки" } );
    m_restrictions.append( { "Мичуринск", "ЬУВМ", "Сатурн", "UUR300", "GND", "350", "14.00", "15.00" , "Парашютные прыжки" } );
}

int RestrictionModel::rowCount(const QModelIndex &) const
{
    return m_restrictions.count();
}

QVariant RestrictionModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount())
    {
        switch (role) {
        case AdRole:
            return m_restrictions.at(index.row()).ad;
        case IndxMilRole:
            return m_restrictions.at(index.row()).indxMil;
        case CallSignRole:
            return m_restrictions.at(index.row()).callSign;
        case ZoneRole:
            return m_restrictions.at(index.row()).zone;
        case LevelFromRole:
            return m_restrictions.at(index.row()).levelFrom;
        case LevelToRole:
            return m_restrictions.at(index.row()).levelTo;
        case TimeFromRole:
            return m_restrictions.at(index.row()).timeFrom;
        case TimeToRole:
            return m_restrictions.at(index.row()).timeTo;
        case NoteRole:
            return m_restrictions.at(index.row()).note;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QHash<int, QByteArray> RestrictionModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { AdRole, "ad" },
        { IndxMilRole, "indxMil" },
        { CallSignRole, "callSign" },
        { ZoneRole, "zone" },
        { LevelFromRole, "levelFrom" },
        { LevelToRole, "levelTo" },
        { TimeFromRole, "timeFrom" },
        { TimeToRole, "timeTo" },
        { NoteRole, "note" }
    };
    return roles;
}

QVariantMap RestrictionModel::get(int row) const
{
    const Restriction restriction = m_restrictions.value(row);
    return {
        { "ad", restriction.ad },
        { "indxMil", restriction.indxMil },
        { "callSign", restriction.callSign },
        { "zone", restriction.zone },
        { "levelFrom", restriction.levelFrom },
        { "levelTo", restriction.levelTo },
        { "timeFrom", restriction.timeFrom },
        { "timeTo", restriction.timeTo },
        { "note", restriction.note }
    };
}

void RestrictionModel::append(const QString &ad,
                              const QString &indxMil,
                              const QString &callSign,
                              const QString &zone,
                              const QString &levelFrom,
                              const QString &levelTo,
                              const QString &timeFrom,
                              const QString &timeTo,
                              const QString &note)
{
//    int row = 0;
//    while (row < m_restrictions.count() && label > m_restrictions.at(row).label)
//        ++row;
    int row = m_restrictions.count();

    beginInsertRows(QModelIndex(), row, row);
    m_restrictions.insert(row, { ad, indxMil, callSign, zone, levelFrom, levelTo, timeFrom, timeTo, note } );
    endInsertRows();
}

void RestrictionModel::set(int row,
                           const QString &ad,
                           const QString &indxMil,
                           const QString &callSign,
                           const QString &zone,
                           const QString &levelFrom,
                           const QString &levelTo,
                           const QString &timeFrom,
                           const QString &timeTo,
                           const QString &note)
{
    if (row < 0 || row >= m_restrictions.count())
        return;

    m_restrictions.replace(row, { ad, indxMil, callSign, zone, levelFrom, levelTo, timeFrom, timeTo, note });
    dataChanged(index(row, 0),
                index(row, 0),
                { AdRole, IndxMilRole, CallSignRole, ZoneRole, LevelFromRole, LevelToRole, TimeFromRole, TimeToRole, NoteRole });
}

void RestrictionModel::remove(int row)
{
    if (row < 0 || row >= m_restrictions.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_restrictions.removeAt(row);
    endRemoveRows();
}
