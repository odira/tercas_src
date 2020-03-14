#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>

class TotalMonthModel : public QSqlTableModel
{
    Q_OBJECT

public:
    TotalMonthModel(QObject *parent = Q_NULLPTR);

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QStringList roleNamesList() const;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant get(int row, int col) const;

    enum Columns {
        TotalMonthModel_year = 0,
        TotalMonthModel_01,
        TotalMonthModel_02,
        TotalMonthModel_03,
        TotalMonthModel_04,
        TotalMonthModel_05,
        TotalMonthModel_06,
        TotalMonthModel_07,
        TotalMonthModel_08,
        TotalMonthModel_09,
        TotalMonthModel_10,
        TotalMonthModel_11,
        TotalMonthModel_12,
        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    void generateRoleNames();
    void update();

private:
    QHash<int, QByteArray> m_roleNames;
};
