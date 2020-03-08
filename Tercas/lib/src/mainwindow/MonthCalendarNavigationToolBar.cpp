#include "MonthCalendarNavigationToolBar.h"

#include <QToolButton>

VyborgMonthCalendarNavigationToolbar::VyborgMonthCalendarNavigationToolbar(QWidget *parent)
    : QToolBar(parent)
{
//    QToolButton *btest = new QToolButton;
    addAction(QString("TEST"));
}
