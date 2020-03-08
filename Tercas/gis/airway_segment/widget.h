#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTableView;
QT_END_NAMESPACE
class RelationalTableModel;


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

private slots:
    void openMapperDialog(const QModelIndex &indx);
    void add();
    void remove();

private:
    RelationalTableModel *m_model;
    QTableView *m_view;
};

#endif // WIDGET_H
