#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
//class QColorDialog;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class ColorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString colorStr READ colorStr WRITE setColorStr NOTIFY colorStrChanged USER true)

public:
    explicit ColorWidget(QWidget *parent = nullptr);

    QString colorStr() const { return m_colorStr; }
    void setColorStr(const QString &colorStr);

signals:
    void colorStrChanged(QString colorStr);

private slots:
    void showColorDialog();
    void setColor(QColor color);

private:
    QString m_colorStr;

    QLabel *m_label;
    QPushButton *m_button;
//    QColorDialog *m_colorDialog;
};

#endif // COLORWIDGET_H
