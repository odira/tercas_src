#ifndef VYBORGYEARMONTH_H
#define VYBORGYEARMONTH_H

#include <QPainter>
#include <QString>

class VyborgYearMonth
{
public:
    VyborgYearMonth(QString year = "", QString month = "");

    void paint(QPainter *painter, const QRect &rect);
    QSize sizeHint() const;

private:
    QString year_;
    QString month_;
};

#endif // VYBORGYEARMONTH_H
