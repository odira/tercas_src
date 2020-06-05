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
        person_pid = 0,
        person_valid,
        person_surname,
        person_name,
        person_middlename,
        person_birthday,
        person_mobile_phone,
        person_tab_num,
        person_position,
        person_class,
        person_shift_num,
        person_sectors_pool,
        person_service_period,
        person_admission,
        person_note,
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

    QHash<int, QByteArray> m_roleNames;
};
