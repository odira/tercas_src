#include <QtWidgets>


//#include "../model/EmplSheduleIntervalModel.h"
#include "EmplSheduleIntervalModel.h"
#include "mapperdialog.h"
#include "mapperdelegate.h"
#include "DateSelect.h"

#include "personwidget.h"


MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_personWidget = new PersonWidget;
    m_activityComboBox = new QComboBox;
    m_startDateSelect = new DateSelect(this);
    m_endDateSelect = new DateSelect(this);
    m_intervalAllSpinBox = new QSpinBox;
    m_intervalWorkSpinBox = new QSpinBox;
    m_notePTE = new QPlainTextEdit;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_personWidget, EmplSheduleIntervalModel::Columns::column_person_pid, "pid");
    m_mapper->addMapping(m_activityComboBox, EmplSheduleIntervalModel::Columns::column_activity_activity);
    m_mapper->addMapping(m_startDateSelect, EmplSheduleIntervalModel::Columns::column_start_date, "date");
    m_mapper->addMapping(m_endDateSelect, EmplSheduleIntervalModel::Columns::column_end_date, "date");
    m_mapper->addMapping(m_notePTE, EmplSheduleIntervalModel::Columns::column_note);

    m_mapper->setItemDelegate(new MapperDelegate);

    connect(m_startDateSelect, SIGNAL(dateChanged(QDate)),
            this, SLOT(startDateChanged(QDate)));
    connect(m_endDateSelect, SIGNAL(dateChanged(QDate)),
            this, SLOT(endDateChanged(QDate)));
}

void MapperDialog::layoutPrivateWidgets()
{
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(new QLabel(tr("Начало")));
    hLayout1->addWidget(m_startDateSelect);
    hLayout1->addWidget(new QLabel(tr("Окончание")));
    hLayout1->addWidget(m_endDateSelect);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(new QLabel(tr("Всего дней")));
    hLayout2->addWidget(m_intervalAllSpinBox);
    hLayout2->addWidget(new QLabel(tr("из них рабочих")));
    hLayout2->addWidget(m_intervalWorkSpinBox);
    hLayout2->addStretch(1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    QGroupBox *dateGroup = new QGroupBox;
    dateGroup->setLayout(vLayout);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(m_personWidget);
    formLayout->addRow(QString(tr("Вид деятельности")), m_activityComboBox);
    formLayout->addRow(dateGroup);
    formLayout->addRow(m_notePTE);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(formLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Normal)
    {
        m_personWidget->setEnabled(false);
        m_activityComboBox->setEditable(false);
        m_startDateSelect->setEditable(false);
        m_endDateSelect->setEditable(false);
        m_intervalAllSpinBox->setEnabled(false);
        m_intervalWorkSpinBox->setEnabled(false);
        m_notePTE->setEnabled(false);
    }
    else
    {
        m_personWidget->setEnabled(true);
        m_personWidget->setFocus();
        m_activityComboBox->setEditable(true);
        m_startDateSelect->setEditable(true);
        m_endDateSelect->setEditable(true);
        m_intervalAllSpinBox->setEnabled(true);
        m_intervalWorkSpinBox->setEnabled(true);
        m_notePTE->setEnabled(true);
    }
}

void MapperDialog::startDateChanged(const QDate &date)
{
    QDate endDate = m_endDateSelect->date();
    int interval_ = date.daysTo(endDate) + 1;
    m_intervalAllSpinBox->setValue(interval_);
}

void MapperDialog::endDateChanged(const QDate &date)
{
    QDate startDate = m_startDateSelect->date();
    int interval_ = startDate.daysTo(date) + 1;
    m_intervalAllSpinBox->setValue(interval_);
}
