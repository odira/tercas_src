#include <QtWidgets>

#include "mapperdialog.h"
#include "declarations.h"
#include "AbbrColorWidget.h"
#include "mapperdelegate.h"

MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
//    m_monthyearDateEdit = new QDateEdit;
//    m_monthyearDateEdit->setDisplayFormat("yyyy MMMM dd");
//    m_departmentComboBox = new QComboBox;
//    m_volLineEdit = new QLineEdit;

    m_abbrcolorW = new AbbrColorWidget;

    m_colorLE = new QLineEdit;
    m_abbrLE = new QLineEdit;
    m_entactivityLE = new QLineEdit;
    m_noteruPTE = new QPlainTextEdit;

    QDataWidgetMapper* m_mapper = mapper();
//    m_mapper->addMapping(m_colorLE, entactivity_color);
//    m_mapper->addMapping(m_abbrLE, entactivity_abbr);
    m_mapper->addMapping(m_entactivityLE, entactivity_entactivity);
    m_mapper->addMapping(m_noteruPTE, entactivity_noteru);
//    m_mapper->addMapping(m_abbrcolorW, entactivity_abbr, "abbr");
    m_mapper->addMapping(m_abbrcolorW, entactivity_color, "color");
}

void MapperDialog::layoutPrivateWidgets()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(m_abbrcolorW);
    formLayout->addRow(QString(trUtf8("Цвет")), m_colorLE);
    formLayout->addRow(QString(trUtf8("Обозначение")), m_abbrLE);
    formLayout->addRow(QString(trUtf8("Активность")), m_entactivityLE);
    formLayout->addRow(QString(trUtf8("Примечание")), m_noteruPTE);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(formLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Normal) {
//        m_dateEdit->setReadOnly(true);
////        m_shiftEdit->setReadOnly(true);
//        m_locationEdit->setReadOnly(true);
//        m_causeEdit->setReadOnly(true);
//        m_factorEdit->setReadOnly(true);
//        m_detailsEdit->setReadOnly(true);
////        m_sectorEdit->setReadOnly(true);
//        m_accCombo->setEditable(false);
//        m_classificationCombo->setEditable(false);
//        m_typeCombo->setEditable(false);
//        m_terkasCombo->setEditable(false);
//        m_alphaCombo->setEditable(false);
//        m_tcas1Combo->setEditable(false);
//        m_tcas2Combo->setEditable(false);
    } else {
//        m_dateEdit->setReadOnly(false);
////        m_shiftEdit->setReadOnly(false);
//        m_locationEdit->setReadOnly(false);
//        m_causeEdit->setReadOnly(false);
//        m_factorEdit->setReadOnly(false);
//        m_detailsEdit->setReadOnly(false);
////        m_sectorEdit->setReadOnly(false);
//        m_accCombo->setEditable(true);
//        m_classificationCombo->setEditable(true);
//        m_typeCombo->setEditable(true);
//        m_terkasCombo->setEditable(true);
//        m_alphaCombo->setEditable(true);
//        m_tcas1Combo->setEditable(true);
//        m_tcas2Combo->setEditable(true);

//        m_dateEdit->setFocus();
    }
}
