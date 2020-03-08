#include <QtWidgets>
#include <QtSql>
#include <QString>

#include "SectorPidArrayWidget.h"

SectorPidArrayWidget::SectorPidArrayWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f),
      m_sectorPidArr()
{
    m_sectorPidArrLE = new QLineEdit;

    m_plusButton = new QPushButton("+");
    m_minusButton = new QPushButton("±");

    connect(m_plusButton, SIGNAL(clicked(bool)),
            this, SLOT(showPlainSectorsListW()));


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(5);
    mainLayout->addWidget(m_sectorPidArrLE);
    mainLayout->addWidget(m_plusButton);
    mainLayout->addWidget(m_minusButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

#include <QDebug>
void SectorPidArrayWidget::setArray(const QString &arrayStr)
{
    if (arrayStr != arrayToString(m_sectorPidArr))
    {
        m_sectorPidArr = stringToArray(arrayStr);
        emit arrayChanged(arrayToString(m_sectorPidArr));

        m_sectorPidArrLE->clear();
        for (int i = 0; i < m_sectorPidArr.size(); ++i)
        {
            QString queryStr = QString("SELECT label FROM fir.vw_sector WHERE pid=%1").arg(m_sectorPidArr.at(i));
//            QString queryStr = QString("SELECT label FROM fir.sector WHERE pid=%1").arg(m_sectorPidArr.at(i));
            QSqlQuery query(queryStr);
            while (query.next()) {
                QString labelStr = query.value(0).toString();
                m_sectorPidArrLE->setText(QString(m_sectorPidArrLE->text() + labelStr));
            }
        }
    }
}

QString SectorPidArrayWidget::array() const
{
    return arrayToString(m_sectorPidArr);
}

QList<int> SectorPidArrayWidget::stringToArray(const QString &arrayStr)
{
    m_sectorPidArr.clear();

    QString subStr = arrayStr.mid(1, arrayStr.length() - 2);
    if (subStr.isEmpty()) {
        return QList<int>();
    }

    QStringList arrayStrList = subStr.split(',', QString::SkipEmptyParts);
    foreach (QString s, arrayStrList) {
        m_sectorPidArr << s.toInt();
    }

    return m_sectorPidArr;
}

QString SectorPidArrayWidget::arrayToString(QList<int> array) const
{
    if (array.isEmpty()) {
        return QString("{}");
    }

    QStringList arrayStrList;
    foreach (int i, array) {
        arrayStrList << QString::number(i);
    }

    QString arrayStr = QString("{") + arrayStrList.join(",") + QString("}");
    return arrayStr;
}

void SectorPidArrayWidget::showPlainSectorsListW()
{
    m_plainSectorsListW = new PlainSectorsListWidget;
    connect(m_plainSectorsListW, SIGNAL(addSectorSignal(int)),
            this, SLOT(addSectorPid(int)));
    m_plainSectorsListW->show();
}

void SectorPidArrayWidget::addSectorPid(int pid)
{
    qDebug() << pid;
    m_sectorPidArr << pid;
}


PlainSectorsListWidget::PlainSectorsListWidget(QWidget *parent)
    : QWidget(parent)
{
    QString queryStr("SELECT pid,label FROM fir.vw_sector WHERE compound IS false AND array_length(sectorpidarr, 1)=1");
//    QString queryStr("SELECT pid,label FROM fir.sector WHERE compound IS false ORDER BY label"); // WHERE compound IS false AND array_length(sectorpidarr, 1)=1");
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(queryStr);

    m_comboBox = new QComboBox;
    m_comboBox->setModel(model);
    m_comboBox->setModelColumn(1);

    connect(m_comboBox, SIGNAL(activated(int)),
            this, SLOT(sectorActivated(int)));
//    connect(m_comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
//            [=](int index){ /* .... */});

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_comboBox);

    setLayout(mainLayout);
}

void PlainSectorsListWidget::sectorActivated(int row)
{
    QModelIndex idx = m_comboBox->model()->index(row, 0);
    int pid = m_comboBox->model()->data(idx).toInt();

    emit addSectorSignal(pid);

    this->close();
}
