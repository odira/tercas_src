#ifndef VYBORGSORTDIALOG_H
#define VYBORGSORTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
//class QSortFilterProxyModel;
class QSqlTableModel;
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

class VyborgSortDialog : public QDialog
{
    Q_OBJECT

public:
    VyborgSortDialog(QSqlTableModel *model = 0, QWidget *parent = 0);
//    VyborgSortDialog(QSortFilterProxyModel *proxy = 0, QWidget *parent = 0);

    void setModel(QSqlTableModel *model);
    void addColumn(const QString & columnText, const int columnData);
    void addColumn(const QString & columnText, const QString & columnData);

private slots:
    void sort();
    void close();

private:
    QComboBox   *columnComboBox;
    QComboBox   *orderComboBox;
    QCheckBox   *caseSensitivityCheckBox;
    QSqlTableModel *m_model;
//    QSortFilterProxyModel *proxy_;
};

#endif // VYBORGSORTDIALOG_H
