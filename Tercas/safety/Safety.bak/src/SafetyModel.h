#ifndef SAFETYMODEL_H
#define SAFETYMODEL_H

#include <QSqlTableModel>

class SafetyModel : public QSqlTableModel
{
    Q_OBJECT

public:
    SafetyModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QHash<int, QByteArray> roleNames() const { return m_roleNames; }
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant get(int row) const;

private:
    void generateRoleNames();

private:
    QHash<int, QByteArray> m_roleNames;
};

#endif // SAFETYMODEL_H
