#include "yearmonthday.h"

const int PaintingScaleFactor = 60;


VyborgYearMonthDay::VyborgYearMonthDay(QString year, QString month, QString day)
    : year_(year), month_(month), day_(day)
{
}

void VyborgYearMonthDay::paint(QPainter *painter, const QRect &rect)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(QBrush(Qt::yellow));
    painter->setPen(QPen(Qt::blue));

    int xOffset = (rect.width() - PaintingScaleFactor) / 2;
    int yOffset = (rect.height() - PaintingScaleFactor) / 2;
    painter->translate(rect.x() + xOffset,
                       rect.y() + yOffset);


    painter->drawRect(0, 0, 60, 30);

    painter->drawRect(0, 30, 60, 30);


    QFont font("Verdana");
//    int fontPixelSize_ = 12;
//    font.setPixelSize(fontPixelSize_);
    QFontMetrics fm(font);
    painter->setFont(font);

    QRectF rectMonth(QPointF(2, 2), QSize(56, 26));
    painter->drawText(rectMonth, Qt::AlignCenter, QString(day_ + " " + month_));

    QRectF rectYear(QPointF(2, 32), QSize(56, 26));
    painter->drawText(rectYear, Qt::AlignCenter, year_);
}

QSize VyborgYearMonthDay::sizeHint() const
{
    return PaintingScaleFactor * 1.1 * QSize(1, 1);
}
