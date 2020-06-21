#include <QtWidgets>

#include "../model/EmplActivityModel.h"
#include "mapperdialog.h"
//#include "declarations.h"

// Uncomment if MapperDelegate is used
 #include "mapperdelegate.h"

#include "colorwidget.h"

MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_colorW = new ColorWidget;
    m_activityLE = new QLineEdit;
    m_noteruPTE = new QPlainTextEdit;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_colorW, EmplActivityModel::Columns::activity_pid);
    m_mapper->addMapping(m_activityLE, EmplActivityModel::Columns::activity_activity);
    m_mapper->addMapping(m_noteruPTE, EmplActivityModel::Columns::activity_note);
    m_mapper->setItemDelegate(new MapperDelegate);
}

void MapperDialog::layoutPrivateWidgets()
{
    QLabel *activityLabel = new QLabel(tr("Вид деятельности"));
    activityLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    activityLabel->setBuddy(m_activityLE);

    QLabel *noteruLabel = new QLabel(tr("Примечание"));
    noteruLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    noteruLabel->setBuddy(m_noteruPTE);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_colorW, 0, 2, 1, 1);
    gridLayout->addWidget(activityLabel, 1, 0);
    gridLayout->addWidget(m_activityLE, 1, 1, 1, 2);
    gridLayout->addWidget(noteruLabel, 2, 0);
    gridLayout->addWidget(m_noteruPTE, 2, 1, 1, 2);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(gridLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Normal)
    {
        m_colorW->setEnabled(false);
        m_activityLE->setReadOnly(true);
        m_noteruPTE->setReadOnly(true);
    }
    else
    {
        m_colorW->setEnabled(true);
        m_activityLE->setReadOnly(false);
        m_noteruPTE->setReadOnly(false);
    }
}
