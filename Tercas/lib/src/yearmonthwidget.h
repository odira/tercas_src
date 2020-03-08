#ifndef VYBORGYEARMONTHWIDGET_H
#define VYBORGYEARMONTHWIDGET_H

#include <QWidget>

class VyborgYearMonth;


class VyborgYearMonthWidget : public QWidget
{
    Q_OBJECT

public:
    VyborgYearMonthWidget(QString year = "", QString month = "", QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private:
    VyborgYearMonth *yearMonth_;
};

#endif // VYBORGYEARMONTHWIDGET_H
