#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>

class EmplSheduleYearModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplSheduleYearModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    virtual QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE { return m_roleNames; }
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private slots: // functions
//    QStringList roleNamesList() const;
    void generateRoleNames();
    void update(const QString &notification = QString());

private: // variables
    QHash<int, QByteArray> m_roleNames;
    int m_year;
};
