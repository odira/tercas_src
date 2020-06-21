#ifndef TEAMSHEDULEMONTHMODEL_H
#define TEAMSHEDULEMONTHMODEL_H

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>
#include <QDate>

class TeamSheduleMonthModel: public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int shiftnum READ shiftnum WRITE setShiftnum NOTIFY shiftnumChanged)

public:
    TeamSheduleMonthModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    virtual QHash<int, QByteArray> roleNames() const override { return m_roleNames; }
    QStringList roleNamesList() const;

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QDate date() const { return m_date; }
    Q_INVOKABLE void setDate(const QDate &date);
    Q_INVOKABLE int shiftnum() const { return m_shiftnum; }
    Q_INVOKABLE void setShiftnum(const int &shiftnum);

private:
    void getPersonPidArr();
    void generateRoleNames();
    void update();

signals:
    void dateChanged(const QDate &);
    void shiftnumChanged(int);

private:
    QHash<int, QByteArray> m_roleNames;
    QDate m_date;
    int m_shiftnum;
    QList<int> m_personPidArr;
};

#endif // TEAMSHEDULEMONTHMODEL_H
