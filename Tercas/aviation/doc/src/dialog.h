#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QModelIndex>

class QSqlRelationalTableModel;
class QTableView;


class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_addButtonClicked();
    void on_delButtonClicked();
    void on_editButtonClicked();
    void on_exportPdfButtonClicked();
    void on_aboutButtonClicked();
    void on_viewDoubleClicked(QModelIndex);

private:
    QSqlRelationalTableModel *m_model;
    QTableView *m_view;
};

#endif // DIALOG_H
