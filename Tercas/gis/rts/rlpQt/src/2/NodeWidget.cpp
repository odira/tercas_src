#include <QtWidgets>

#include "NodeWidget.h"

NodeWidget::NodeWidget(QWidget *parent)
    : QWidget(parent), m_latgg(0), m_latmm(0), m_latss(0.0), m_longg(0), m_lonmm(0), m_lonss(0.0), m_srid(-1), m_noteru(QString())
{
    m_latggLineEdit = new QLineEdit;
    m_latmmLineEdit = new QLineEdit;
    m_latssLineEdit = new QLineEdit;
    m_longgLineEdit = new QLineEdit;
    m_lonmmLineEdit = new QLineEdit;
    m_lonssLineEdit = new QLineEdit;
    m_sridLineEdit = new QLineEdit;
    m_noteruPTE = new QPlainTextEdit;

    QGridLayout *latGrid = new QGridLayout;
    latGrid->setContentsMargins(5, 5, 5, 5);
    latGrid->setSpacing(0);
    latGrid->addWidget(m_latggLineEdit, 0, 0);
    latGrid->addWidget(m_latmmLineEdit, 0, 1);
    latGrid->addWidget(m_latssLineEdit, 0, 2);

    QGroupBox *latGroup = new QGroupBox(trUtf8("Широта"));
    latGroup->setLayout(latGrid);

    QGridLayout *lonGrid = new QGridLayout;
    lonGrid->setContentsMargins(5, 5, 5, 5);
    lonGrid->setSpacing(0);
    lonGrid->addWidget(m_longgLineEdit, 0, 0);
    lonGrid->addWidget(m_lonmmLineEdit, 0, 1);
    lonGrid->addWidget(m_lonssLineEdit, 0, 2);

    QGroupBox *lonGroup = new QGroupBox(trUtf8("Долгота"));
    lonGroup->setLayout(lonGrid);

    QGridLayout *sridGrid = new QGridLayout;
    sridGrid->setContentsMargins(5, 5, 5, 5);
    sridGrid->addWidget(m_sridLineEdit);

    QGroupBox *sridGroup = new QGroupBox(trUtf8("SRID"));
    sridGroup->setLayout(sridGrid);

    QHBoxLayout *coordLayout = new QHBoxLayout;
    coordLayout->addWidget(latGroup);
    coordLayout->addWidget(lonGroup);
    coordLayout->addWidget(sridGroup);

    QVBoxLayout *noteLayout = new QVBoxLayout;
    noteLayout->setContentsMargins(5, 5, 5, 5);
    noteLayout->addWidget(m_noteruPTE);

    QGroupBox *noteGroup = new QGroupBox(trUtf8("Примечание"));
    noteGroup->setLayout(noteLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(coordLayout);
    mainLayout->addWidget(noteGroup);

    setLayout(mainLayout);
}
