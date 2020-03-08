#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"

#include <QSqlTableModel>

class SafetyModel : public QSqlTableModel
{
    Q_OBJECT

public:
    SafetyModel(QObject *parent = Q_NULLPTR);

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    enum Columns {
        SafetyModel_pid = 0,
        SafetyModel_ts,
        SafetyModel_accpid,
        SafetyModel_acc,
        SafetyModel_departmentpid,
        SafetyModel_department,
        SafetyModel_shift,
        SafetyModel_sectorpid,
        SafetyModel_sector,
        SafetyModel_sectorlabel,
        SafetyModel_sectorcolor,
        SafetyModel_node_pid,
        SafetyModel_classificationpid,
        SafetyModel_classification,
        SafetyModel_classificationabbr,
        SafetyModel_typepid,
        SafetyModel_type,
        SafetyModel_cause,
        SafetyModel_factor,
        SafetyModel_details,
        SafetyModel_note,
        SafetyModel_spospid,
        SafetyModel_spos,
        SafetyModel_tcas1pid,
        SafetyModel_tcas1,
        SafetyModel_tcas2pid,
        SafetyModel_tcas2,
        ColumnsNumber
    };
    Q_ENUM(Columns)

private:
    void generateRoleNames();
    void update();

private:
    QHash<int, QByteArray> m_roleNames;
};
