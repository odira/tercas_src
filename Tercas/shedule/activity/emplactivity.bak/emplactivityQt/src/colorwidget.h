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

class ColorWidget : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(int pid READ pid WRITE setPid NOTIFY pidChanged USER true)
    Q_PROPERTY(int pid READ pid WRITE setPid USER true)
    Q_PROPERTY(QColor color READ color)
    Q_PROPERTY(QString abbr READ abbr)

public:
    explicit ColorWidget(QWidget *parent = 0);

    int pid() const;
    void setPid(int const &pid);

    QColor color() const;
    QString abbr() const;

    void setEnabled(bool enabled);

//signals:
//    void pidChanged(const int &pid);

private slots:
    void showColorDialog();
    void colorChanged(const QColor &color);
    void abbrChanged(const QString &abbr);

private:
    int m_pid;
    QColor m_color;
    QString m_abbr;

    QLineEdit *m_lineEdit;
    QPushButton *m_button;
    QColorDialog *m_colorDialog;
};

#endif // COLORWIDGET_H
