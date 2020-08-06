#pragma once

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLE "calendar.vw_holiday"

#include <QDate>
#include <QSqlTableModel>

class HolidayModel : public QSqlTableModel
{
    Q_OBJECT

//    Q_PROPERTY(QDate   date READ date WRITE setDate NOTIFY dateChanged)
//    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
//    Q_PROPERTY(QString note READ note WRITE setNote NOTIFY noteChanged)

public:

    enum HolidayRoles {
         DateRole = Qt::UserRole + 1
        ,TypeRole
        ,NoteRole
    };
    Q_ENUM(HolidayRoles)

public:
    HolidayModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    virtual QHash<int, QByteArray> roleNames() const { return m_roleNames; }

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &idx, const QVariant &value, int role = Qt::EditRole);




//    Q_INVOKABLE bool submitDB();
//    Q_INVOKABLE void revertDB();

//    Q_INVOKABLE QVariant get(int row) const;
//    Q_INVOKABLE bool set(int row, QVariant value, QString role);
//    Q_INVOKABLE bool deleteRow(int row);
//    Q_INVOKABLE void add(QDate date, QString type, QString noteRu);

//    Q_INVOKABLE void save(int pid, QDate date, QString type, QString note);
//    Q_INVOKABLE void add();

//    void setDate(const QDate   &/*date*/) { emit dateChanged(); }
//    void setType(const QString &/*type*/) { emit typeChanged(); }
//    void setNote(const QString &/*note*/) { emit noteChanged(); }

private:
    void generateRoleNames();
    void update();

//signals:
//    void dateChanged();
//    void typeChanged();
//    void noteChanged();

private:
    QHash<int, QByteArray> m_roleNames;
};

