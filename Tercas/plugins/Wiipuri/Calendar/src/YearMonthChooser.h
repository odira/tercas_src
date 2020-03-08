#ifndef YEARMONTHCHOOSER_H
#define YEARMONTHCHOOSER_H

#include <QQuickItem>

class YearMonthChooser : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(YearMonthChooser)

public:
    YearMonthChooser(QQuickItem *parent = nullptr);
    ~YearMonthChooser();
};

#endif // YEARMONTHCHOOSER_H
