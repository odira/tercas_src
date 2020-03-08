#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>
#include <QDate>

class EmplSheduleMonthModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int shiftnum READ shiftnum WRITE setShiftnum NOTIFY shiftnumChanged)
    Q_PROPERTY(int sectorspool READ sectorspool WRITE setSectorspool NOTIFY sectorspoolChanged)
    Q_PROPERTY(QStringList roleNamesList READ roleNamesList CONSTANT)

public:
    EmplSheduleMonthModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QStringList roleNamesList() const;

    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE bool isHoliday(QDate date) const;
    Q_INVOKABLE bool isDayOff(QDate date) const;

    Q_INVOKABLE QVariant get(int personpid, int day) const;
    Q_INVOKABLE QVariant getPersonPid(int row) const;
    Q_INVOKABLE QVariant getColor(int row, int column) const;
    Q_INVOKABLE QVariant getAbbr(int personpid, int day) const;
    Q_INVOKABLE QVariant getToolTip(int personpid, int day) const;
    Q_INVOKABLE QVariant getNumberAvailable(int day) const;

    Q_INVOKABLE QDate date() const { return m_date; }
    Q_INVOKABLE void setDate(const QDate &date);
    Q_INVOKABLE int shiftnum() const { return m_shiftnum; }
    Q_INVOKABLE void setShiftnum(const int &shiftnum);
    Q_INVOKABLE int sectorspool() const { return m_sectorspool; }
    Q_INVOKABLE void setSectorspool(const int &sectorspool);

signals:
    void dateChanged(const QDate &);
    void shiftnumChanged();
    void sectorspoolChanged();

private:
    void generateRoleNames();
    void update();

    QHash<int, QByteArray> m_roleNames;
    QList<int> m_personPidArray;
    QDate m_date;
    int m_shiftnum;
    int m_sectorspool;
};
