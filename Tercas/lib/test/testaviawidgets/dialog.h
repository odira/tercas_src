#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class GeogWidget;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private slots:
    void buttonClicked();

private:
    QPushButton *button;
    GeogWidget *geogWidget;
};

#endif // DIALOG_H
