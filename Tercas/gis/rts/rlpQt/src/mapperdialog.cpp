#include <QtWidgets>

#include "mapperdialog.h"
#include "../model/GisRlpModel.h"
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
    m_rlpLE = new QLineEdit;
    m_noteruPTE = new QPlainTextEdit;
    m_nodeW = new NodeWidget;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_rlpLE, GisRlpModel::Columns::rlp_name);
    m_mapper->addMapping(m_nodeW, GisRlpModel::Columns::rlp_nodepid);
    m_mapper->addMapping(m_noteruPTE, GisRlpModel::Columns::rlp_noteru);
}

void MapperDialog::layoutPrivateWidgets()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(QString(trUtf8("РЛП")), m_rlpLE);
    formLayout->addRow(QString(trUtf8("Координаты")), m_nodeW);
    formLayout->addRow(QString(trUtf8("Примечание")), m_noteruPTE);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(formLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Normal) {
        m_rlpLE->setReadOnly(true);
        m_nodeW->setEnabled(false);
        m_noteruPTE->setReadOnly(true);
    } else {
        m_rlpLE->setReadOnly(false);
        m_nodeW->setEnabled(true);
        m_noteruPTE->setReadOnly(false);

        m_rlpLE->setFocus();
    }
}
