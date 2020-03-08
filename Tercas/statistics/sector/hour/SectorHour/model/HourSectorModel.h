#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlQueryModel>
#include <QDate>

struct Sector {
    int pid;
    QString label;
    int npsdz = 0;
    int npspdz = 0;
};

class HourSectorModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged USER true)
    Q_PROPERTY(QStringList roleNamesList READ roleNamesList CONSTANT)

public:
    HourSectorModel(QObject *parent = Q_NULLPTR);
    HourSectorModel(QDate date, QObject *parent = Q_NULLPTR);

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QStringList roleNamesList() const;
    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QDate date() { return m_date; }

    Q_INVOKABLE QVariant getSectorLabel(int rowNum) const;
    Q_INVOKABLE QVariant getSectorValue(int rowNum, int hour) const;
    Q_INVOKABLE QVariant getSectorColor(int rowNum, int hour) const;

    enum Columns {
        hoursector_sector_pid = 0,
        hoursector_hh00,
        hoursector_hh01,
        hoursector_hh02,
        hoursector_hh03,
        hoursector_hh04,
        hoursector_hh05,
        hoursector_hh06,
        hoursector_hh07,
        hoursector_hh08,
        hoursector_hh09,
        hoursector_hh10,
        hoursector_hh11,
        hoursector_hh12,
        hoursector_hh13,
        hoursector_hh14,
        hoursector_hh15,
        hoursector_hh16,
        hoursector_hh17,
        hoursector_hh18,
        hoursector_hh19,
        hoursector_hh20,
        hoursector_hh21,
        hoursector_hh22,
        hoursector_hh23,
        ColumnsNumber
    };
    Q_ENUM(Columns)

public slots:
    Q_INVOKABLE void setDate(const QDate &date);

signals:
    void dateChanged(const QDate &date);

private:
    void createSectorList();
    void generateRoleNames();
    void update();

private:
    QDate m_date;
    QList<Sector *> m_sectors;
    QHash<int, QByteArray> m_roleNames;
};
