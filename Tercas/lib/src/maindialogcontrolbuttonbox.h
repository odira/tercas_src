#ifndef VYBORGMAINDIALOGCONTROLBUTTONBOX_H
#define VYBORGMAINDIALOGCONTROLBUTTONBOX_H

#include <QDialogButtonBox>


class VyborgMainDialogControlButtonBox : public QDialogButtonBox
{
    Q_OBJECT

public:
    VyborgMainDialogControlButtonBox(QWidget *parent = 0);

//    void addButton(QPushButton *button);

signals:
    void sort();
    void filter();
    void update();
    void add();
    void remove();
    void about();
    void close();

private slots:
    void on_sortButtonClicked();
    void on_filterButtonClicked();
    void on_updateButtonClicked();
    void on_addButtonClicked();
    void on_removeButtonClicked();
    void on_aboutButtonClicked();
    void on_closeButtonClicked();
};

#endif // VYBORGMAINDIALOGCONTROLBUTTONBOX_H
