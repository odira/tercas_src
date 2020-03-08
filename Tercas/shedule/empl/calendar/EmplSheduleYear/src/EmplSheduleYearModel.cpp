#include <QSqlDriver>
#include <QSqlQuery>
#include <QtSql>

#include "EmplSheduleYearModel.h"

EmplSheduleYearModel::EmplSheduleYearModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel (parent)
{
    Q_UNUSED(db)

    m_year = 2020;


    QSqlDatabase dbCurrent = QSqlDatabase::database();
    QSqlDriver *driver = dbCurrent.driver();

    if (!driver->subscribeToNotification("empl_shedule")) {
        qCritical() << "Notification \"empl_shedule\" not subscribed..." << endl << "Quiting the app...";
        qApp->quit();
    } else
        connect(driver, SIGNAL(notification(const QString &)), this, SLOT(update(const QString &)));

//    connect(driver, QOverload<const QString &>::of(&QSqlDriver::notification),
//          [=](const QString &name){ /* ... */ });

    generateRoleNames();

    setTable("shedule.vw_empl_shedule_year_ct");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    update();
}

//QStringList EmplSheduleYearModel::roleNamesList() const
//{
//    QMap<int, QString> res;
//    QHashIterator<int, QByteArray> i(m_roleNames);
//    while (i.hasNext()) {
//        i.next();
//        if (i.key() > Qt::UserRole)
//            res[i.key()] = i.value();
//    }
//    return res.values();
//}

void EmplSheduleYearModel::generateRoleNames()
{
    m_roleNames.clear();

    m_roleNames[Qt::DisplayRole] = QVariant(QString("display").toUtf8()).toByteArray();
    m_roleNames[Qt::BackgroundRole] = QVariant(QString("background").toUtf8()).toByteArray();

//    // calculate number of days in year
//    int daysRoleCount = 366;

//    // first role is 'person' role
//    m_roleNames[Qt::UserRole + 1] = QVariant(QString("person").toUtf8()).toByteArray();
//    // other roles is array counting from 1 to number of days in year
//    for (int i = 1; i <= daysRoleCount; i++)
//        m_roleNames[Qt::UserRole + 1 + i] = QVariant(QString::number(i).toUtf8()).toByteArray();
}

void EmplSheduleYearModel::update(const QString &notification)
{
    Q_UNUSED(notification)
    beginResetModel();
    select();
    endResetModel();
}

int EmplSheduleYearModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 15;
}

int EmplSheduleYearModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    int daysInYear = (m_year % 4) == 0 ? 366 : 365;
    return 1 + daysInYear; // First column for person's name, other columns for day roles
}

QVariant EmplSheduleYearModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int row = idx.row();
    int col = idx.column();

    if (col < 0 || col > columnCount())
        return QVariant();

    if (row < 0 || row > rowCount())
        return QVariant();


    QVariant data = QSqlTableModel::data(idx);
    if (data.isNull())
        return QVariant();

    if (col == 0) // person column
    {
        switch (role)
        {

        case Qt::DisplayRole: {
            qint16 personPid = data.toInt();
            QString queryStr = QString("SELECT surname FROM person.vw_person WHERE pid=%1;")
                    .arg(personPid);
            QSqlQuery query(queryStr);
            while (query.next()) {
                QString surnameStr = query.value(0).toString();
                return surnameStr;
            }
            return QVariant();
        }

        case Qt::BackgroundRole: {
            return QColor("yellow").name();
        }

        } // switch
    }
    else // day number column
    {
        switch (role)
        {

        case Qt::DisplayRole: {
            return QVariant();
        }

        case Qt::BackgroundRole: {
            return QColor("red").name();
        }
        } // switch
    }

    return QVariant();
}

QVariant EmplSheduleYearModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < 0)
        return QVariant();

    if (orientation == Qt::Vertical)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (role) {
        case Qt::DisplayRole:
            return QString::number(section);
        }
    }

    return QVariant();
}
