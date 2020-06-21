#include <QtWidgets>

#include "../model/EmplSectorCheckModel.h"

#include "mapperdialog.h"
#include "mapperdelegate.h"

#include "PersonWidget.h"
#include "SectorWidget.h"
#include "DateSelect.h"


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
    m_sectorW = new SectorWidget;
    m_dateW = new DateSelect;
    m_typeCB = new QComboBox;

    QSqlQueryModel *sectorcheckModel = new QSqlQueryModel;
    sectorcheckModel->setQuery("SELECT unnest( enum_range(NULL::shedule.t_sector_check) )");
    m_typeCB->setModel(sectorcheckModel);

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_personW, EmplSectorCheckModel::Columns::column_personpid);
    m_mapper->addMapping(m_typeCB, EmplSectorCheckModel::Columns::column_type);
    m_mapper->addMapping(m_sectorW, EmplSectorCheckModel::Columns::column_sectorpid);
    m_mapper->addMapping(m_dateW, EmplSectorCheckModel::Columns::column_date);

//    m_mapper->setItemDelegate(new MapperDelegate);
}

void MapperDialog::layoutPrivateWidgets()
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_sectorW);
    hLayout->addStretch(1);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(m_personW);
    formLayout->addRow(QString(tr("Детализация")), m_typeCB);
    formLayout->addRow(hLayout);
    formLayout->addRow(QString(tr("Дата")), m_dateW);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(formLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Normal)
    {
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
    }
    else
    {
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
