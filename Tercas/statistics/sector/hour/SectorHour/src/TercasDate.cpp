#include "TercasDate.h"

TercasDate::TercasDate(QObject *parent)
    : QObject(parent)
{
    m_date = QDate::currentDate();
}

int TercasDate::nightShift() const
{
    qint64 jDate = m_date.toJulianDay();
    int tempShift = (int)(jDate % 6) + 1;

    if (tempShift == 6)
        return 4;
    else if (tempShift == 5)
        return 3;
    else if (tempShift == 4)
        return 2;
    else if (tempShift == 3)
        return 1;
    else if (tempShift == 2)
        return 6;
    else if (tempShift == 1)
        return 5;

    return 0;
}

int TercasDate::morningShift() const
{
    qint64 jDate = m_date.toJulianDay();
    int tempShift = (int)(jDate % 6) + 1;

    if (tempShift == 6)
        return 2;
    else if (tempShift == 5)
        return 1;
    else if (tempShift == 4)
        return 6;
    else if (tempShift == 3)
        return 5;
    else if (tempShift == 2)
        return 4;
    else if (tempShift == 1)
        return 3;

    return 0;
}

int TercasDate::daylightShift() const
{
    qint64 jDate = m_date.toJulianDay();
    int tempShift = (int)(jDate % 6) + 1;

    if (tempShift == 6)
        return 1;
    else if (tempShift == 5)
        return 6;
    else if (tempShift == 4)
        return 5;
    else if (tempShift == 3)
        return 4;
    else if (tempShift == 2)
        return 3;
    else if (tempShift == 1)
        return 2;

    return 0;
}

int TercasDate::eveningShift() const
{
    qint64 jDate = m_date.toJulianDay();
    int tempShift = (int)(jDate % 6) + 1;

    if (tempShift == 6)
        return 3;
    else if (tempShift == 5)
        return 2;
    else if (tempShift == 4)
        return 1;
    else if (tempShift == 3)
        return 6;
    else if (tempShift == 2)
        return 5;
    else if (tempShift == 1)
        return 4;

    return 0;
}
