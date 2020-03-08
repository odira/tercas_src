#include <QtWidgets>

#include "aboutdialog.h"


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    QPixmap image(":/share/images/about.jpg");
    QLabel *label = new QLabel;
    label->setPixmap(image);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    setLayout(mainLayout);
}
