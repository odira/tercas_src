#include <QSqlQuery>

#include "TotalMonthModel.h"

TotalMonthModel::TotalMonthModel(QObject *parent)
    : QSqlTableModel(parent)
{
    generateRoleNames();
    update();
}

void TotalMonthModel::generateRoleNames()
{
    m_roleNames.clear();

    m_roleNames[Qt::UserRole + 1]      = QVariant(QString("year").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 1 ] = QVariant(QString("jan").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 2 ] = QVariant(QString("feb").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 3 ] = QVariant(QString("mar").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 4 ] = QVariant(QString("apr").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 5 ] = QVariant(QString("may").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 6 ] = QVariant(QString("jun").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 7 ] = QVariant(QString("jul").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 8 ] = QVariant(QString("aug").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 9 ] = QVariant(QString("sep").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 10] = QVariant(QString("oct").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 11] = QVariant(QString("nov").toUtf8()).toByteArray();
    m_roleNames[Qt::UserRole + 1 + 12] = QVariant(QString("dec").toUtf8()).toByteArray();
}

QStringList TotalMonthModel::roleNamesList() const
{
    QMap<int, QString> res;
    QHashIterator<int, QByteArray> i(m_roleNames);
    while (i.hasNext()) {
        i.next();
        if (i.key() > Qt::UserRole) {
            res[i.key()] = i.value();
        }
    }
    return res.values();
}

void TotalMonthModel::update()
{
    beginResetModel();

    QString queryStr = QString(
        "SELECT * FROM crosstab( "
            "'SELECT year, month, sum FROM "
                    "(SELECT extract(year FROM date) AS year, extract(month FROM date) AS month, sum(load) FROM "
                    "statistics.total_date GROUP BY extract(month FROM date), extract(year FROM date) ORDER BY year, month) temp ORDER BY 1' ,"
            "'SELECT m FROM generate_series(1,12) m'"
        ") AS ("
        "year int,"
        "jan int,"
        "feb int,"
        "mar int,"
        "apr int,"
        "may int,"
        "jun int,"
        "jul int,"
        "aug int,"
        "sep int,"
        "oct int,"
        "nov int,"
        "dec int)"
    );
    QSqlQuery query(queryStr);
    setQuery(query);

    endResetModel();
}

int TotalMonthModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsNumber;
}

QVariant TotalMonthModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    int row = idx.row();

    if (col < 0 || col > columnCount())
        return QVariant();

    if (row < 0 || row > rowCount())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return QSqlTableModel::data(createIndex(row, col)).toInt();
    }
    else if (role > Qt::UserRole)
    {
        int col = role - Qt::UserRole - 1;
        int vol = QSqlTableModel::data(createIndex(row, col), Qt::DisplayRole).toInt();
        return vol;
    }

    return QVariant();
}

QVariant TotalMonthModel::get(int row, int col) const
{
    return this->data(createIndex(row, col + 1), Qt::DisplayRole);
}
