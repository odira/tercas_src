#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLE "calendar.vw_holiday"

#include <QDate>
#include <QSqlTableModel>

class HolidayModel : public QSqlTableModel
{
    Q_OBJECT

public:

    enum Columns {
        Column_pid        = 0,
        Column_date,     // 1
        Column_type_pid, // 2
        Column_type,     // 3
        Column_note,     // 4

        ColumnsNumber
    };
    Q_ENUM(Columns)

public:
    HolidayModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
//    QStringList roleNamesList() const;

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &idx, const QVariant &value, int role = Qt::EditRole);

//    Q_INVOKABLE bool submitDB();
//    Q_INVOKABLE void revertDB();

//    Q_INVOKABLE QVariant get(int row) const;
//    Q_INVOKABLE bool set(int row, QVariant value, QString role);
//    Q_INVOKABLE bool deleteRow(int row);
//    Q_INVOKABLE void add(QDate date, QString type, QString noteRu);

    Q_INVOKABLE void save(int pid, QDate date, QString type, QString note);

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
};

