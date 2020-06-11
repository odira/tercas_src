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
        column_pid = 0,
        column_valid,
        column_surname,
        column_name,
        column_middlename,
        column_birthday,
        column_mobile_phone,
        column_tab_num,
        column_position,
        column_class,
        column_shift_num,
        column_sectors_pool,
        column_service_period,
        column_admission,
        column_note,

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
