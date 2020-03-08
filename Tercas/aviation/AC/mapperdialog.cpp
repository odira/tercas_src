#include <QtWidgets>
#include <QtSql>

#include "mapperdialog.h"
#include "declarations.h"


MapperDialog::MapperDialog(QSortFilterProxyModel *proxy, QWidget *parent)
    : VyborgMapperDialog(proxy, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    ICAOlineEdit    = new QLineEdit;
    IATAlineEdit    = new QLineEdit;
    codeRuLineEdit  = new QLineEdit;
    CSlineEdit      = new QLineEdit;
    CSruLineEdit    = new QLineEdit;
    AClineEdit      = new QLineEdit;
    ACruLineEdit    = new QLineEdit;
    fleetTextEdit   = new QTextEdit;
    noteTextEdit    = new QTextEdit;
    noteRuTextEdit  = new QTextEdit;
    countryLineEdit = new QLineEdit;
    pointLineEdit   = new QLineEdit;


    mapper_->addMapping(ICAOlineEdit,    AC_ICAO);
    mapper_->addMapping(IATAlineEdit,    AC_IATA);
    mapper_->addMapping(codeRuLineEdit,  AC_codeRu);
    mapper_->addMapping(CSlineEdit,      AC_CS);
    mapper_->addMapping(CSruLineEdit,    AC_CSru);
    mapper_->addMapping(AClineEdit,      AC_AC);
    mapper_->addMapping(ACruLineEdit,    AC_ACru);
    mapper_->addMapping(fleetTextEdit,   AC_fleet);
    mapper_->addMapping(noteTextEdit,    AC_note);
    mapper_->addMapping(noteRuTextEdit,  AC_noteRu);
    mapper_->addMapping(countryLineEdit, AC_country_id);
    mapper_->addMapping(pointLineEdit,   AC_point_id);
}

void MapperDialog::layoutPrivateWidgets()
{
    QLabel *ICAOlabel = new QLabel(trUtf8("ICAO:"));
    ICAOlabel->setBuddy(ICAOlineEdit);

    QLabel *IATAlabel = new QLabel(trUtf8("IATA:"));
    IATAlabel->setBuddy(IATAlineEdit);

    QLabel *codeRuLabel = new QLabel(trUtf8("RU Code:"));
    codeRuLabel->setBuddy(codeRuLineEdit);

    QLabel *CSlabel = new QLabel(trUtf8("Callsign:"));
    CSlabel->setBuddy(CSlineEdit);

    QLabel *CSruLabel = new QLabel(trUtf8("RU Callsign:"));
    CSruLabel->setBuddy(CSruLineEdit);

    QLabel *AClabel = new QLabel(trUtf8("Name:"));
    AClabel->setBuddy(AClineEdit);

    QLabel *ACruLabel = new QLabel(trUtf8("RU Name:"));
    ACruLabel->setBuddy(AClineEdit);

    QLabel *fleetLabel = new QLabel(trUtf8("Fleet:"));
    fleetLabel->setBuddy(fleetTextEdit);

    QLabel *noteLabel = new QLabel(trUtf8("Note:"));
    noteLabel->setBuddy(noteTextEdit);

    QLabel *noteRuLabel = new QLabel(trUtf8("RU Name:"));
    noteRuLabel->setBuddy(noteRuTextEdit);

    QLabel *countryLabel = new QLabel(trUtf8("Country:"));
    countryLabel->setBuddy(countryLineEdit);

    QLabel *pointLabel = new QLabel(trUtf8("Point:"));
    pointLabel->setBuddy(pointLineEdit);


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(ICAOlabel,     0, 0, 1, 1);   gridLayout->addWidget(ICAOlineEdit,     0, 1, 1, 1);
    gridLayout->addWidget(IATAlabel,     1, 0, 1, 1);   gridLayout->addWidget(IATAlineEdit,     1, 1, 1, 1);
    gridLayout->addWidget(codeRuLabel,   2, 0, 1, 1);   gridLayout->addWidget(codeRuLineEdit,   2, 1, 1, 1);
    gridLayout->addWidget(CSlabel,       3, 0, 1, 1);   gridLayout->addWidget(CSlineEdit,       3, 1, 1, 1);
    gridLayout->addWidget(CSruLabel,     4, 0, 1, 1);   gridLayout->addWidget(CSruLineEdit,     4, 1, 1, 1);
    gridLayout->addWidget(AClabel,       5, 0, 1, 1);   gridLayout->addWidget(AClineEdit,       5, 1, 1, 1);
    gridLayout->addWidget(ACruLabel,     6, 0, 1, 1);   gridLayout->addWidget(ACruLineEdit,     6, 1, 1, 1);
    gridLayout->addWidget(fleetLabel,    7, 0, 1, 1);   gridLayout->addWidget(fleetTextEdit,    7, 1, 1, 1);
    gridLayout->addWidget(noteLabel,     8, 0, 1, 1);   gridLayout->addWidget(noteTextEdit,     8, 1, 1, 1);
    gridLayout->addWidget(noteRuLabel,   9, 0, 1, 1);   gridLayout->addWidget(noteRuTextEdit,   9, 1, 1, 1);
    gridLayout->addWidget(countryLabel, 10, 0, 1, 1);   gridLayout->addWidget(countryLineEdit, 10, 1, 1, 1);
    gridLayout->addWidget(pointLabel,   11, 0, 1, 1);   gridLayout->addWidget(pointLineEdit,   11, 1, 1, 1);

    privateWidgetsLayout->addLayout(gridLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (dirty_ == true)
    {
        ICAOlineEdit->setReadOnly(false);
        IATAlineEdit->setReadOnly(false);
        codeRuLineEdit->setReadOnly(false);
        CSlineEdit->setReadOnly(false);
        CSruLineEdit->setReadOnly(false);
        AClineEdit->setReadOnly(false);
        ACruLineEdit->setReadOnly(false);
        fleetTextEdit->setReadOnly(false);
        noteTextEdit->setReadOnly(false);
        noteRuTextEdit->setReadOnly(false);
        countryLineEdit->setReadOnly(false);
        pointLineEdit->setReadOnly(false);

        ICAOlineEdit->setFocus();
    }
    else
    {
        ICAOlineEdit->setReadOnly(true);
        IATAlineEdit->setReadOnly(true);
        codeRuLineEdit->setReadOnly(true);
        CSlineEdit->setReadOnly(true);
        CSruLineEdit->setReadOnly(true);
        AClineEdit->setReadOnly(true);
        ACruLineEdit->setReadOnly(true);
        fleetTextEdit->setReadOnly(true);
        noteTextEdit->setReadOnly(true);
        noteRuTextEdit->setReadOnly(true);
        countryLineEdit->setReadOnly(true);
        pointLineEdit->setReadOnly(true);
    }
}
