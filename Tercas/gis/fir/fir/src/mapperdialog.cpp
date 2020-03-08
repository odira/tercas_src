#include <QtWidgets>
#include <QtSql>

#include "mapperdialog.h"
#include "declarations.h"
#include "nodepidarraytablewidget.h"

MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_firLE = new QLineEdit;
    m_fullnameLE = new QLineEdit;
    m_nodeArrayW = new NodePidArrayTableWidget;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_firLE, fir_fir);
    m_mapper->addMapping(m_fullnameLE, fir_fullname);
    m_mapper->addMapping(m_nodeArrayW, fir_nodepidarr, "nodepidarr");
}

void MapperDialog::layoutPrivateWidgets()
{
    QFormLayout *formLayout1 = new QFormLayout;
    formLayout1->addRow(trUtf8("FIR"), m_firLE);
    formLayout1->addRow(trUtf8("Полное\nнаименование"), m_fullnameLE);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout1);
    mainLayout->addWidget(m_nodeArrayW);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(mainLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Edit || state() == Add)
    {
        m_firLE->setReadOnly(false);
        m_fullnameLE->setReadOnly(false);

        m_nodeArrayW->setEnabled(true);
    }
    else
    {
        m_firLE->setReadOnly(true);
        m_fullnameLE->setReadOnly(true);

        m_nodeArrayW->setEnabled(false);
    }
}
