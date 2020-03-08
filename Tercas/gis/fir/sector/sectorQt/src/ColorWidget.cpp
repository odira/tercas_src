#include <QLabel>
#include <QPushButton>
//#include <QPixmap>
#include <QPainter>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QColorDialog>

#include "ColorWidget.h"

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget(parent), m_colorStr(QString())
{
    m_label = new QLabel(m_colorStr);
    m_button = new QPushButton(trUtf8("Change color.."));
    connect(m_button, SIGNAL(clicked(bool)),
            this, SLOT(showColorDialog()));

    QHBoxLayout *lLayout = new QHBoxLayout;
    lLayout->addWidget(m_label);
    lLayout->addWidget(m_button);

    QGroupBox *groupBox = new QGroupBox(trUtf8("Цвет"));
    groupBox->setLayout(lLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
}

void ColorWidget::setColorStr(const QString &colorStr)
{
    if (colorStr != m_colorStr) {
        m_colorStr = colorStr;

        QPixmap pix(QSize(29, 29));
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(QColor(m_colorStr));
        p.drawRect(QRect(-1, -1, 31, 31));
        m_label->setPixmap(pix);

        emit colorStrChanged(m_colorStr);
    }
}

void ColorWidget::setColor(QColor color)
{
    QString colorStr = color.name();
    setColorStr(colorStr);
}

void ColorWidget::showColorDialog()
{
    QColor color(m_colorStr);
    QColorDialog *m_colorDialog = new QColorDialog(QColor(color));
    connect(m_colorDialog, SIGNAL(colorSelected(QColor)),
            this, SLOT(setColor(QColor)));
    m_colorDialog->open();
}
