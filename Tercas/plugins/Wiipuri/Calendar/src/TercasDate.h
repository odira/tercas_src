#pragma once

#include <QObject>
#include <QDate>

class TercasDate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

public:
    TercasDate(QObject *parent = Q_NULLPTR);
    TercasDate(int year, int month, int day, QObject *parent = Q_NULLPTR);

    ~TercasDate() { }

    Q_INVOKABLE qint64 julianDay();
    Q_INVOKABLE bool isShiftWorking(QDate date, int shift);

signals:
    void dateChanged(QDate date);

private:
    QDate date() const { return m_date; }
    void setDate(const QDate &date) { m_date = date; emit dateChanged(m_date); }

private:
    QDate m_date;
};

