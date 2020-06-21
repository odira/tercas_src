#include <QtWidgets>

#include "mapperdialog.h"
#include "../model/SectorWorktimeModel.h"
#include "PersonWidget.h"
#include "SectorWidget.h"


// Uncomment if MapperDelegate is used
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
    m_personW = new PersonWidget;
//    m_personfullnameLE = new QLineEdit;
//    m_sectorlabelLE = new QLineEdit;
    m_sectorW = new SectorWidget;
    m_sector_posCB = new QComboBox;
    m_startdateDE = new QDateEdit;
    m_starttimeTE = new QTimeEdit;
    m_enddateDE = new QDateEdit;
    m_endtimeTE = new QTimeEdit;
    m_intervalTE = new QTimeEdit;
    m_notePTE = new QPlainTextEdit;

//    m_monthyearDateEdit = new QDateEdit;
//    m_monthyearDateEdit->setDisplayFormat("yyyy MMMM dd");
//    m_departmentComboBox = new QComboBox;
//    m_volLineEdit = new QLineEdit;

    QDataWidgetMapper* m_mapper = mapper();
//    m_mapper->addMapping(m_personfullnameLE, SectorWorktimeModel::column_personfullname);
    m_mapper->addMapping(m_personW, SectorWorktimeModel::column_personpid);
//    m_mapper->addMapping(m_sectorlabelLE, SectorWorktimeModel::column_sectorlabel);
    m_mapper->addMapping(m_sectorW, SectorWorktimeModel::column_sectorpid);
    m_mapper->addMapping(m_sector_posCB, SectorWorktimeModel::column_sector_pos);
    m_mapper->addMapping(m_startdateDE, SectorWorktimeModel::column_startdate);
    m_mapper->addMapping(m_starttimeTE, SectorWorktimeModel::column_starttime);
    m_mapper->addMapping(m_enddateDE, SectorWorktimeModel::column_enddate);
    m_mapper->addMapping(m_endtimeTE, SectorWorktimeModel::column_endtime);
    m_mapper->addMapping(m_intervalTE, SectorWorktimeModel::column_interval);
    m_mapper->addMapping(m_notePTE, SectorWorktimeModel::column_note);

    m_mapper->setItemDelegate(new MapperDelegate);
}

void MapperDialog::layoutPrivateWidgets()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(m_personW);
//    formLayout->addRow(QString(trUtf8("Работник")), m_personfullnameLE);
    formLayout->addRow(QString(trUtf8("Сектор")), m_sectorW);
    formLayout->addRow(QString(trUtf8("Место")), m_sector_posCB);
    formLayout->addRow(QString(trUtf8("Дата начала")), m_startdateDE);
    formLayout->addRow(QString(trUtf8("Время начала")), m_starttimeTE);
    formLayout->addRow(QString(trUtf8("Дата окончания")), m_enddateDE);
    formLayout->addRow(QString(trUtf8("Время окончания")), m_endtimeTE);
    formLayout->addRow(QString(trUtf8("Продолжительность")), m_intervalTE);
    formLayout->addRow(QString(trUtf8("Примечание")), m_notePTE);

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
