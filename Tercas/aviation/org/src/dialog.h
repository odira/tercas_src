#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class TableModel;


class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private slots:
    void on_closeButton_clicked();

    void on_exportButton_clicked();

    void on_editButton_clicked();

private:
    Ui::Dialog *ui;
    TableModel *m_model;
};

#endif // DIALOG_H
