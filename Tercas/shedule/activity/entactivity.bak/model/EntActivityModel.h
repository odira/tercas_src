#define once

#include <QSqlTableModel>

class EntActivityModel : public QSqlTableModel
{
    Q_OBJECT

public:
    EntActivityModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};
