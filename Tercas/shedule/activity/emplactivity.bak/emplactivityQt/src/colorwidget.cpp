#include <QtWidgets>
#include <QtSql>

#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget(parent), m_pid(-1)
{
    m_lineEdit = new QLineEdit;
    m_lineEdit->setFixedWidth(38);
    m_lineEdit->setFixedHeight(30);
    m_lineEdit->setAlignment(Qt::AlignCenter);

    m_button = new QPushButton("...");

    QGroupBox *abbrGroupBox = new QGroupBox(trUtf8("Отображение"));

    QHBoxLayout *hLayout = new QHBoxLayout(abbrGroupBox);
    hLayout->setSpacing(5);
    hLayout->addWidget(m_lineEdit);
    hLayout->addWidget(m_button);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(abbrGroupBox);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    connect(m_lineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(abbrChanged(QString)));
    connect(m_button, SIGNAL(clicked(bool)),
            this, SLOT(showColorDialog()));
}

int ColorWidget::pid() const
{
    return m_pid;
}

void ColorWidget::setPid(const int &pid)
{
    if (pid != m_pid)
    {
        m_pid = pid;
//        emit pidChanged(m_pid);

        QString queryString = QString("SELECT abbr,color FROM shedule.vw_empl   activity WHERE pid = %1")
                .arg(m_pid);
        QSqlQuery query(queryString);
        while (query.next()) {
            QString abbr = query.value(0).toString();
            QString colorString = query.value(1).toString();

            m_abbr = abbr;
            m_color = QColor(colorString);

            m_lineEdit->setText(abbr);
            m_lineEdit->setStyleSheet(QString("background-color:'%1'").arg(colorString));
        }
    }
}

QColor ColorWidget::color() const
{
    return m_color;
}

QString ColorWidget::abbr() const
{
    return m_abbr;
}

void ColorWidget::setEnabled(bool enabled)
{
    m_lineEdit->setReadOnly(!enabled);
    m_button->setEnabled(enabled);
}

void ColorWidget::showColorDialog()
{
    m_colorDialog = new QColorDialog(this);
    connect(m_colorDialog, SIGNAL(colorSelected(QColor)),
            this, SLOT(colorChanged(QColor)));
    m_colorDialog->exec();
}

void ColorWidget::abbrChanged(const QString &abbr)
{
    m_abbr = abbr;
}

void ColorWidget::colorChanged(const QColor &color)
{
//    QString colorString = color.name();
//    QString queryString = QString("UPDATE shedule.activity SET color='%1' WHERE pid=%2").arg(colorString).arg(m_pid);
//    QSqlQuery query(queryString);
//    query.exec();
    m_color = color;
}
