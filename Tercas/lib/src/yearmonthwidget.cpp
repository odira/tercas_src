#include <QtWidgets>

#include "yearmonthwidget.h"
#include "yearmonth.h"

VyborgYearMonthWidget::VyborgYearMonthWidget(QString year, QString month, QWidget *parent)
    : QWidget(parent)
{
    yearMonth_ = new VyborgYearMonth(year, month);
}

void VyborgYearMonthWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    QRect rect(0, 0, this->width(), this->height());

    yearMonth_->paint(&painter, rect);
}

QSize VyborgYearMonthWidget::sizeHint() const
{
    return yearMonth_->sizeHint();
}

QSize VyborgYearMonthWidget::minimumSizeHint() const
{
    return VyborgYearMonthWidget::sizeHint();
}
