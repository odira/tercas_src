#include "TercasDate.h"

TercasDate::TercasDate(QObject *parent)
    : QObject(parent)
{
    m_date = QDate();
}

TercasDate::TercasDate(int year, int month, int day, QObject *parent)
    : QObject(parent), m_date(year, month, day)
{ }

qint64 TercasDate::julianDay()
{
    return m_date.toJulianDay();
}

bool TercasDate::isShiftWorking(QDate date, int shift)
{
    setDate(date);
    qint64 sDate = (julianDay() + shift) % 6;
    if (sDate == 0 || sDate == 1 || sDate == 2 || sDate == 3)
        return true;

    return false;
}
