#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>
#include <QDate>

struct Sector {
    int pid;
    QString label;
    QString color;
};

class SectorMonthModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

public:
    SectorMonthModel(QObject *parent = Q_NULLPTR);

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QDate date() const { return m_date; }

    Q_INVOKABLE QVariant getModelYear() const { return m_date.year(); };
    Q_INVOKABLE QVariant getSectorLabel(int row) const;
    Q_INVOKABLE QVariant getSectorLoad(int row, int day) const;
    Q_INVOKABLE QVariant getSectorColor(int row) const;

    enum Columns {
        SectorMonthModel_sector_pid = 0,
        SectorMonthModel_01,
        SectorMonthModel_02,
        SectorMonthModel_03,
        SectorMonthModel_04,
        SectorMonthModel_05,
        SectorMonthModel_06,
        SectorMonthModel_07,
        SectorMonthModel_08,
        SectorMonthModel_09,
        SectorMonthModel_10,
        SectorMonthModel_11,
        SectorMonthModel_12,
        SectorMonthModel_sector_total,
        ColumnsNumber
    };
    Q_ENUM(Columns)

public slots:
    Q_INVOKABLE void setDate(const QDate &date);

signals:
    void dateChanged(QDate date);

private:
    void createSectorsList();
    void generateRoleNames();
    void update();

private:
    QHash<int, QByteArray> m_roleNames;
    QList<Sector *> m_sectors;
    QDate m_date;
};
