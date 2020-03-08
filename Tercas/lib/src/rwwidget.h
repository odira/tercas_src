#ifndef RWWIDGET_H
#define RWWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTableView;
class QPushButton;
QT_END_NAMESPACE

class RWTableModel;

class RWWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int adid READ adid WRITE setAdid NOTIFY adidChanged USER true)

public:
    RWWidget(QWidget *parent = 0);

    void setAdid(const int &adid);
    int adid() const;

signals:
    void adidChanged();

private slots:
    void onEditButtonClicked();
    void onAddButtonClicked();
    void onSaveButtonClicked();
    void onRevertButtonClicked();

private:
    QTableView   *m_tableView;
    QPushButton  *m_editButton;
    QPushButton  *m_addButton;
    QPushButton  *m_saveButton;
    QPushButton  *m_revertButton;
    RWTableModel *m_model;

    int m_adid;
};



#include <QSqlTableModel>

class RWTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    RWTableModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const Q_DECL_OVERRIDE;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int m_adid;
};

#endif // RWWIDGET_H
