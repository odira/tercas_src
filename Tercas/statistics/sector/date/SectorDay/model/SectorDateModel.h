#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlQueryModel>
#include <QDate>

struct Sector {
    int pid;
    QString label;
};

class SectorDateModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList roleNamesList READ roleNamesList CONSTANT)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

public:
    SectorDateModel(QObject *parent = Q_NULLPTR);

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QStringList roleNamesList() const;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QDate date() const { return m_date; }

    Q_INVOKABLE QVariant getSectorLabel(int row) const;
    Q_INVOKABLE QVariant getSectorLoad(int row, int day) const;

    enum Columns {
        SectorDateModel_sector_pid = 0,
        SectorDateModel_dd00,
        SectorDateModel_dd01,
        SectorDateModel_dd02,
        SectorDateModel_dd03,
        SectorDateModel_dd04,
        SectorDateModel_dd05,
        SectorDateModel_dd06,
        SectorDateModel_dd07,
        SectorDateModel_dd08,
        SectorDateModel_dd09,
        SectorDateModel_dd10,
        SectorDateModel_dd11,
        SectorDateModel_dd12,
        SectorDateModel_dd13,
        SectorDateModel_dd14,
        SectorDateModel_dd15,
        SectorDateModel_dd16,
        SectorDateModel_dd17,
        SectorDateModel_dd18,
        SectorDateModel_dd19,
        SectorDateModel_dd20,
        SectorDateModel_dd21,
        SectorDateModel_dd22,
        SectorDateModel_dd23,
        SectorDateModel_dd24,
        SectorDateModel_dd25,
        SectorDateModel_dd26,
        SectorDateModel_dd27,
        SectorDateModel_dd28,
        SectorDateModel_dd29,
        SectorDateModel_dd30,
        SectorDateModel_dd31,
        ColumnsNumber
    };
    Q_ENUM(Columns)

public slots:
    Q_INVOKABLE void setDate(const QDate &date);

signals:
    void dateChanged(QDate date);

private:
    void createSectorList();
    void generateRoleNames();
    void update();

private:
    QHash<int, QByteArray> m_roleNames;
    QList<Sector *> m_sectors;
    QDate m_date;
};
