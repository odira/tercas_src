#pragma once

#include <QSqlTableModel>

class EmplActivityModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EmplActivityModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::EditRole) const;
};
