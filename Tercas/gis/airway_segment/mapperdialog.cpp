#include <QtWidgets>
#include <QtSql>

#include "mapperdialog.h"
#include "declarations.h"
#include "relationaltablemodel.h"


MapperDialog::MapperDialog(RelationalTableModel *model, int indx, QWidget *parent)
    : QDialog(parent)
{
    m_model = model;

    m_mapper = new QDataWidgetMapper;
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    m_mapper->setModel(m_model);
    m_mapper->setItemDelegate(new QSqlRelationalDelegate(m_mapper));



    QLabel *lLabel = new QLabel(trUtf8("Название"));
    QComboBox *cbAirway = new QComboBox;
    QSqlTableModel *modelAirway = m_model->relationModel(col_airway);
    cbAirway->setModel(modelAirway);
    cbAirway->setModelColumn(modelAirway->fieldIndex("airway"));
    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(cbAirway);


    QLabel *lPoint = new QLabel(trUtf8("Точки"));
    QComboBox *cbPoint1 = new QComboBox;
    QSqlTableModel *modelPoint1 = m_model->relationModel(col_first_point);
    cbPoint1->setModel(modelPoint1);
    cbPoint1->setModelColumn(modelPoint1->fieldIndex("label"));
    cbPoint1->model()->sort(1);
    QComboBox *cbPoint2 = new QComboBox;
    QSqlTableModel *modelPoint2 = m_model->relationModel(col_second_point);
    cbPoint2->setModel(modelPoint2);
    cbPoint2->setModelColumn(modelPoint2->fieldIndex("label"));
    cbPoint2->model()->sort(1);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(cbPoint1);
    hbox->addWidget(cbPoint2);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(lLabel, hbox2);
    formLayout->addRow(lPoint, hbox);


    QPlainTextEdit *pteNote = new QPlainTextEdit;


    QPushButton *pbToFirst = new QPushButton(trUtf8("First"));
    QPushButton *pbToPrev = new QPushButton(trUtf8("Previous"));
    QPushButton *pbToNext = new QPushButton(trUtf8("Next"));
    QPushButton *pbToLast = new QPushButton(trUtf8("Last"));

    connect(pbToFirst, SIGNAL(clicked()),
            m_mapper, SLOT(toFirst()));
    connect(pbToPrev, SIGNAL(clicked()),
            m_mapper, SLOT(toPrevious()));
    connect(pbToNext, SIGNAL(clicked()),
            m_mapper, SLOT(toNext()));
    connect(pbToLast, SIGNAL(clicked()),
            m_mapper, SLOT(toLast()));

    QDialogButtonBox *navbbox = new QDialogButtonBox(Qt::Horizontal);
    navbbox->addButton(pbToFirst, QDialogButtonBox::ActionRole);
    navbbox->addButton(pbToPrev, QDialogButtonBox::ActionRole);
    navbbox->addButton(pbToNext, QDialogButtonBox::ActionRole);
    navbbox->addButton(pbToLast, QDialogButtonBox::ActionRole);


    QPushButton *pbSave = new QPushButton(trUtf8("Save"));
    QPushButton *pbClose = new QPushButton(trUtf8("Close"));

    connect(pbSave, SIGNAL(clicked()),
            this, SLOT(save()));
    connect(pbClose, SIGNAL(clicked()),
            this, SLOT(close()));

    QDialogButtonBox *bbox = new QDialogButtonBox(Qt::Vertical);
    bbox->addButton(pbSave, QDialogButtonBox::ActionRole);
    bbox->addButton(pbClose, QDialogButtonBox::ActionRole);

//    QLabel *lSource = new QLabel(trUtf8("Сведения"));
//    QComboBox *cbSource = new QComboBox;
//    QSqlTableModel *modelSource = m_model->relationModel(col_source);
//    cbSource->setModel(modelSource);
//    cbSource->setModelColumn(modelSource->fieldIndex("doc"));
//    QHBoxLayout *hbox3 = new QHBoxLayout;
//    hbox3->addWidget(lSource);
//    hbox3->addWidget(cbSource);



    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(formLayout);
    vLayout->addWidget(pteNote);
//    vLayout->addLayout(hbox3);
    vLayout->addWidget(navbbox);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(vLayout);
    mainLayout->addWidget(bbox);

    setLayout(mainLayout);


    m_mapper->addMapping(cbAirway, col_airway);
    m_mapper->addMapping(cbPoint1, col_first_point);
    m_mapper->addMapping(cbPoint2, col_second_point);
    m_mapper->addMapping(pteNote, m_model->fieldIndex("note"));

    m_mapper->setCurrentIndex(indx);
}

void MapperDialog::save()
{
    if (!m_mapper->submit())
        qDebug() << "ERROR: " << m_model->lastError().text();
    if (!m_model->submitAll())
        qDebug() << "ERROR: " << m_model->lastError().text();
}
