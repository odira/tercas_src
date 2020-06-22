#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

#include <QColor>
#include <QString>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QColorDialog;
QT_END_NAMESPACE

class AbbrColorWidget : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(int pid READ pid WRITE setPid NOTIFY pidChanged USER true)
//    Q_PROPERTY(int pid READ pid WRITE setPid USER true)
    Q_PROPERTY(QString abbr READ abbr WRITE setAbbr)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit AbbrColorWidget(QWidget *parent = 0);

//    int pid() const;
//    void setPid(int const &pid);

    QString abbr() const;
    void setAbbr(const QString &abbr);
    QColor color() const;
    void setColor(const QColor &color);

    void setEnabled(bool enabled);

//signals:
//    void pidChanged(const int &pid);

private slots:
    void abbrChanged(const QString &abbr);
    void colorChanged(const QColor &color);
    void showColorDialog();

private:
//    int m_pid;
    QColor m_color;
    QString m_abbr;

    QLineEdit *m_lineEdit;
    QPushButton *m_button;
    QColorDialog *m_colorDialog;
};

#endif // COLORWIDGET_H
