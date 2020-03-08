#include <QtWidgets>

#include "dialog.h"
#include "../src/yearmonthwidget.h"
#include "../src/mappercontrolbuttonbox.h"
#include "../src/maindialogcontrolbuttonbox.h"
#include "../src/yearmonth.h"
#include "../src/mapperdialog.h"
#include "../src/navigationbuttonbox.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    VyborgNavigationButtonBox *m_navigationBB = new VyborgNavigationButtonBox;
    m_navigationBB->setCount(10);
    m_navigationBB->setCurrentIndex(5);

    VyborgYearMonthWidget *yearMonthWidget = new VyborgYearMonthWidget("2014", "Fe");


    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(yearMonthWidget);
    hLayout->addStretch();


    VyborgMapperControlButtonBox *controlButtonBox = new VyborgMapperControlButtonBox;
    controlButtonBox->setOrientation(Qt::Vertical);


    VyborgMapperControlButtonBox *mapperControlButtonBox = new VyborgMapperControlButtonBox;
    mapperControlButtonBox->setOrientation(Qt::Vertical);


//    VyborgMapperDialog *dialog = new VyborgMapperDialog;
//    dialog->show();


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_navigationBB);
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(controlButtonBox);
    mainLayout->addWidget(mapperControlButtonBox);


    setLayout(mainLayout);
}
