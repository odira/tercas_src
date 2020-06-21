#ifndef CALDAY_H
#define CALDAY_H

#include <QWidget>
#include <QDate>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QCalendarWidget;
QT_END_NAMESPACE

class DateSelect : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged USER true)

public:
    explicit DateSelect(QWidget *parent = 0);

    void setDate(const QDate &date);
    QDate date() const;

signals:
    void dateChanged(const QDate &date);

public slots:
    bool setEditable(const bool &state);

private slots:
    void showCalendar();
    void closeCalendar(const QDate &date);

private:
    QLineEdit *m_calLineEdit;
    QPushButton *m_calButton;
    QCalendarWidget *m_calCalendar;

    QDate m_date;
};

#endif // CALDAY_H
