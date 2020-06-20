#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QDate>
#include <QSqlTableModel>

class PersonModel : public QSqlTableModel
{
    Q_OBJECT

public:
    enum Columns {
        Column_pid = 0,
        Column_valid,
        Column_surname,
        Column_name,
        Column_middlename,
        Column_birthday,
        Column_mobile_phone,
        Column_tab_num,
        Column_position,
        Column_class,
        Column_shift_num,
        Column_sectors_pool,
        Column_service_period,
        Column_admission,
        Column_note,

        ColumnsNumber
    };
    Q_ENUM(Columns)

public:
    PersonModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    QHash<int, QByteArray> roleNames() const { return m_roleNames; }
//    QStringList roleNamesList() const;

//    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return 10; }
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 10; }


    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &idx, const QVariant &value, int role = Qt::EditRole);

//    Q_INVOKABLE bool submitDB();
//    Q_INVOKABLE void revertDB();

//    Q_INVOKABLE QVariant get(int row) const;
//    Q_INVOKABLE bool set(int row, QVariant value, QString role);
//    Q_INVOKABLE bool deleteRow(int row);
//    Q_INVOKABLE void add(QDate date, QString type, QString noteRu);

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
};
