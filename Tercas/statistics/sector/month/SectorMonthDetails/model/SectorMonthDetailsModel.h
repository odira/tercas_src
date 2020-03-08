#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>
#include <QDate>

struct Sector {
    int pid;
    QString label;
};

class SectorMonthDetailsModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int year WRITE setYear)
    Q_PROPERTY(int month WRITE setMonth)

public:
    SectorMonthDetailsModel(QObject *parent = Q_NULLPTR);

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QDate date() const { return m_date; }

    Q_INVOKABLE QVariant getSectorLabel(int row) const;
    Q_INVOKABLE QVariant getSectorLoad(int row, int day) const;

    enum Columns {
        SectorMonthDetailsModel_sector_pid = 0,
        SectorMonthDetailsModel_sum,
        SectorMonthDetailsModel_max,
        SectorMonthDetailsModel_avg,
        ColumnsNumber
    };
    Q_ENUM(Columns)

public slots:
    Q_INVOKABLE void setDate(const QDate &date);
    Q_INVOKABLE void setYear(const int &year);
    Q_INVOKABLE void setMonth(const int &month);

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
