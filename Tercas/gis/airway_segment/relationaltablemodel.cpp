#include "relationaltablemodel.h"

RelationalTableModel::RelationalTableModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}
