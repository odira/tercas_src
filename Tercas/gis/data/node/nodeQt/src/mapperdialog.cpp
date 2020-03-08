#include <QtWidgets>
#include <QtSql>

#include <vyborg.h>

#include "../model/NodeTableModel.h"
#include "mapperdialog.h"
#include "CoordWidget.h"


MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_coordWid = new CoordWidget;
    m_notePTE = new QPlainTextEdit;

    QDataWidgetMapper* m_mapper = mapper();
//    m_mapper->addMapping(m_coordWid, NodeTableModel::Columns::column_pid);
    m_mapper->addMapping(m_coordWid->getLatLE(), NodeTableModel::Columns::column_lat);
    m_mapper->addMapping(m_coordWid->getLonLE(), NodeTableModel::Columns::column_lon);
    m_mapper->addMapping(m_coordWid->getSridLE(), NodeTableModel::Columns::column_srid);
    m_mapper->addMapping(m_notePTE, NodeTableModel::Columns::column_note);
}

void MapperDialog::layoutPrivateWidgets()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_coordWid);
    mainLayout->addWidget(m_notePTE);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(mainLayout);
}

void MapperDialog::updatePrivateWidgets()
{
//    if (state() == VyborgMapperDialog::Normal)
//    {
//        m_coordWid->setEnabled(false);
//    }
//    else
//    {
//        m_coordWid->setEnabled(true);
//    }
}
