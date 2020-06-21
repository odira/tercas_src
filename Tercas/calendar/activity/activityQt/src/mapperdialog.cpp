#include <QtWidgets>

#include "../model/ActivityModel.h"
#include "mapperdialog.h"
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
    m_coverCB = new QComboBox;
    m_colorW = new ColorWidget;
    m_activityLE = new QLineEdit;
    m_notePTE = new QPlainTextEdit;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_colorW, ActivityModel::Columns::pid);
    m_mapper->addMapping(m_activityLE, ActivityModel::Columns::activity);
    m_mapper->addMapping(m_notePTE, ActivityModel::Columns::note);
    m_mapper->addMapping(m_coverCB, ActivityModel::Columns::path);
    m_mapper->setItemDelegate(new MapperDelegate);
}

void MapperDialog::layoutPrivateWidgets()
{
    QLabel *activityLabel = new QLabel(tr("Вид деятельности"));
    activityLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    activityLabel->setBuddy(m_activityLE);

    QLabel *noteLabel = new QLabel(tr("Примечание"));
    noteLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    noteLabel->setBuddy(m_notePTE);

    QLabel *coverLabel = new QLabel(tr("Path"));
    coverLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    coverLabel->setBuddy(m_coverCB);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_colorW, 0, 2, 1, 1);
    gridLayout->addWidget(coverLabel, 1, 0);
    gridLayout->addWidget(m_coverCB, 1, 1, 1, 2);
    gridLayout->addWidget(activityLabel, 2, 0);
    gridLayout->addWidget(m_activityLE, 2, 1, 1, 2);
    gridLayout->addWidget(noteLabel, 3, 0);
    gridLayout->addWidget(m_notePTE, 3, 1, 1, 2);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(gridLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Normal)
    {
        m_colorW->setEnabled(false);
        m_activityLE->setReadOnly(true);
        m_notePTE->setReadOnly(true);
    }
    else
    {
        m_colorW->setEnabled(true);
        m_activityLE->setReadOnly(false);
        m_notePTE->setReadOnly(false);
    }
}
