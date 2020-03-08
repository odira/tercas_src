#ifndef VYBORGYEARMONTHDAY_H
#define VYBORGYEARMONTHDAY_H

#include <QPainter>
#include <QString>

class VyborgYearMonthDay
{
public:
    VyborgYearMonthDay(QString year = "", QString month = "", QString day = "");

    void paint(QPainter *painter, const QRect &rect);
    QSize sizeHint() const;

private:
    QString year_;
    QString month_;
    QString day_;
};

#endif // VYBORGYEARMONTHDAY_H
