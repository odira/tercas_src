#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QDate>
#include <QSqlTableModel>

class HolidayModel : public QSqlTableModel
{
    Q_OBJECT

public:
    enum Columns {
        holiday_pid = 0,
        holiday_date,
        holiday_type,
        holiday_note_ru,
        ColumnsNumber
    };
    Q_ENUM(Columns)

public:
    HolidayModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QStringList roleNamesList() const;

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &idx, const QVariant &value, int role = Qt::EditRole);

    Q_INVOKABLE bool submitDB();
    Q_INVOKABLE void revertDB();

    Q_INVOKABLE QVariant get(int row) const;
    Q_INVOKABLE bool set(int row, QVariant value, QString role);
    Q_INVOKABLE bool deleteRow(int row);
    Q_INVOKABLE void add(QDate date, QString type, QString noteRu);

private:
    void generateRoleNames();

    QHash<int, QByteArray> m_roleNames;
};

