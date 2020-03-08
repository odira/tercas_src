#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCalendarWidget>
#include <QLocale>

#include "DateSelect.h"

DateSelect::DateSelect(QWidget *parent)
    : QWidget(parent)
{
    m_calLineEdit = new QLineEdit;
    m_calLineEdit->setAlignment(Qt::AlignRight);
    m_calLineEdit->setReadOnly(true);
    m_calButton = new QPushButton(tr("..."));
    m_calCalendar = new QCalendarWidget;
    m_calCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(2);
    hLayout->setMargin(0);
    hLayout->addWidget(m_calLineEdit);
    hLayout->addWidget(m_calButton);

    this->setLayout(hLayout);

    connect(m_calButton, SIGNAL(clicked(bool)),
            this, SLOT(showCalendar()));
    connect(m_calCalendar, SIGNAL(clicked(QDate)),
            this, SLOT(closeCalendar(QDate)));
}

void DateSelect::setDate(const QDate &date)
{
    if (date != m_date) {
        m_date = date;
        emit dateChanged(m_date);

        QLocale ruLocale(QLocale::Russian);
        m_calLineEdit->setText(ruLocale.toString(m_date, QString(tr("dd MMMM yyyy"))));
    }
}

QDate DateSelect::date() const
{
    return m_date;
}

void DateSelect::showCalendar()
{
    m_calCalendar->show();
}

void DateSelect::closeCalendar(const QDate &date)
{
    if (m_calCalendar->close() == true) {
        setDate(date);
    }
}

bool DateSelect::setEditable(const bool &state)
{
    if (state == false)
    {
        m_calButton->setEnabled(false);
    }
    else if (state == true)
    {
        m_calButton->setEnabled(true);
    }
}
