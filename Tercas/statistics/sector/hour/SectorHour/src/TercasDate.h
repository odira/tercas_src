#ifndef TERCASDATE_H
#define TERCASDATE_H

#include <QObject>
#include <QDate>

class TercasDate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate USER true)

public:
    TercasDate(QObject *parent = Q_NULLPTR);

    void setDate(const QDate &date) { m_date = date; }
    QDate date() const { return m_date; }

    Q_INVOKABLE qint64 julianDate() const { return  m_date.toJulianDay(); }
    Q_INVOKABLE int nightShift() const;
    Q_INVOKABLE int morningShift() const;
    Q_INVOKABLE int daylightShift() const;
    Q_INVOKABLE int eveningShift() const;

private:
    QDate m_date;
};

#endif // TERCASDATE_H
