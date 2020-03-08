#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlTableModel>


class TableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;

private slots:
};

#endif // TABLEMODEL_H
