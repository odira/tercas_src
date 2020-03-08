#include <QtWidgets>

#include "mapperdialog.h"
#include "../model/SegmentModel.h"
#include "NodeWidget.h"

// Uncomment if MapperDelegate is used
// #include "mapperdelegate.h"

MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_node1pidNW = new NodeWidget;
    m_node2pidNW = new NodeWidget;
    m_noteruPTE = new QPlainTextEdit;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_node1pidNW, LineSegmentModel::Columns::linesegment_node1pid, "nodepid");
    m_mapper->addMapping(m_node2pidNW, LineSegmentModel::Columns::linesegment_node2pid, "nodepid");
    m_mapper->addMapping(m_noteruPTE, LineSegmentModel::Columns::linesegment_noteru);
//    m_mapper->setItemDelegate(new MapperDelegate);
}

void MapperDialog::layoutPrivateWidgets()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(QString(trUtf8("Примечание")), m_noteruPTE);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addWidget(m_node1pidNW);
    privateWidgetsLayout->addWidget(m_node2pidNW);
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
