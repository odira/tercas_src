#ifndef RELATIONALTABLEMODEL_H
#define RELATIONALTABLEMODEL_H

#include <QSqlRelationalTableModel>

class RelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit RelationalTableModel(QObject *parent = 0);

signals:

public slots:

};

#endif // RELATIONALTABLEMODEL_H
