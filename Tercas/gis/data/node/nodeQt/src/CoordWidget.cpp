#include <QtWidgets>
#include <QtSql>

#include "CoordWidget.h"
#include "convert.h"


CoordWidget::CoordWidget(QWidget *parent)
    : QWidget(parent),
      m_pid(-1), m_latgg(0), m_latmm(0), m_latss(0.0), m_longg(0), m_lonmm(0), m_lonss(0.0), m_srid(-1), m_geog(QString())
{
    m_latggLE  = new QLineEdit;
    m_latmmLE  = new QLineEdit;
    m_latssLE  = new QLineEdit;
    m_latgggLE = new QLineEdit;
    m_longgLE  = new QLineEdit;
    m_lonmmLE  = new QLineEdit;
    m_lonssLE  = new QLineEdit;
    m_longggLE = new QLineEdit;
    m_sridLE   = new QLineEdit;

    m_latggLE->setAlignment(Qt::AlignRight);
    m_latmmLE->setAlignment(Qt::AlignRight);
    m_latssLE->setAlignment(Qt::AlignRight);
    m_latgggLE->setAlignment(Qt::AlignRight);
    m_longgLE->setAlignment(Qt::AlignRight);
    m_lonmmLE->setAlignment(Qt::AlignRight);
    m_lonssLE->setAlignment(Qt::AlignRight);
    m_longggLE->setAlignment(Qt::AlignRight);
    m_sridLE->setAlignment(Qt::AlignRight);

    m_listView = new QListView;

    connect(m_latmmLE, SIGNAL(textEdited(QString)),
            this, SLOT(fieldEdited(QString)));
    connect(m_latssLE, SIGNAL(textEdited(QString)),
            this, SLOT(fieldEdited(QString)));
    connect(m_lonmmLE, SIGNAL(textEdited(QString)),
            this, SLOT(fieldEdited(QString)));
    connect(m_lonssLE, SIGNAL(textEdited(QString)),
            this, SLOT(fieldEdited(QString)));


    QGridLayout *latGrid = new QGridLayout;
    latGrid->setContentsMargins(5, 5, 5, 5);
    latGrid->setSpacing(0);
    latGrid->addWidget(m_latggLE, 0, 0);
    latGrid->addWidget(m_latmmLE, 0, 1);
    latGrid->addWidget(m_latssLE, 0, 2);
    latGrid->addWidget(m_latgggLE, 1, 0, 1, 3);

    QGroupBox *latGroup = new QGroupBox(tr("Широта"));
    latGroup->setLayout(latGrid);

    QGridLayout *lonGrid = new QGridLayout;
    lonGrid->setContentsMargins(5, 5, 5, 5);
    lonGrid->setSpacing(0);
    lonGrid->addWidget(m_longgLE, 0, 0);
    lonGrid->addWidget(m_lonmmLE, 0, 1);
    lonGrid->addWidget(m_lonssLE, 0, 2);
    lonGrid->addWidget(m_longggLE, 1, 0, 1, 3);

    QGroupBox *lonGroup = new QGroupBox(tr("Долгота"));
    lonGroup->setLayout(lonGrid);

    QGridLayout *sridGrid = new QGridLayout;
    sridGrid->setContentsMargins(5, 5, 5, 5);
    sridGrid->addWidget(m_sridLE);

    QGroupBox *sridGroup = new QGroupBox(tr("SRID"));
    sridGroup->setLayout(sridGrid);


    QHBoxLayout *coordLayout = new QHBoxLayout;
    coordLayout->setSpacing(1);
    coordLayout->addWidget(latGroup);
    coordLayout->addWidget(lonGroup);
    coordLayout->addWidget(sridGroup);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(coordLayout);
    mainLayout->addWidget(m_listView);

    setLayout(mainLayout);
}

void CoordWidget::setPid(const int &pid)
{
    if (pid == 0)
    {
        m_latggLE->clear();
        m_latmmLE->clear();
        m_latssLE->clear();
        m_latgggLE->clear();
        m_longgLE->clear();
        m_lonmmLE->clear();
        m_lonssLE->clear();
        m_longggLE->clear();
        m_sridLE->clear();

        return;
    }

    if (pid != m_pid)
    {
        m_pid = pid;
        emit pidChanged(m_pid);

        QString queryStr = QString("SELECT lat,lon,srid FROM data.vw_node WHERE pid=%1")
                .arg(m_pid);
        QSqlQuery query(queryStr);
        while (query.next()) {
            m_lat = query.value(0).toReal();
            m_lon = query.value(1).toReal();
            m_srid = static_cast<qint16>(query.value(2).toInt());
        }

        m_latgg = static_cast<qint8>(m_lat);
        m_longg = static_cast<qint8>(m_lon);

        m_latmm = static_cast<qint8>((m_lat - static_cast<qreal>(m_latgg)) * 60.0);
        m_lonmm = static_cast<qint8>((m_lon - static_cast<qreal>(m_longg)) * 60.0);

        m_latss = ((m_lat - static_cast<qreal>(m_latgg)) * 60.0 - static_cast<qreal>(m_latmm)) * 60.0;
        m_lonss = ((m_lon - static_cast<qreal>(m_longg)) * 60.0 - static_cast<qreal>(m_lonmm)) * 60.0;


        m_latggLE->setText(QString("%1").arg(m_latgg));
        m_longgLE->setText(QString("%1").arg(m_longg));
        m_latmmLE->setText(QString("%1").arg(m_latmm));
        m_lonmmLE->setText(QString("%1").arg(m_lonmm));
        m_latssLE->setText(QString("%1").arg(m_latss));
        m_lonssLE->setText(QString("%1").arg(m_lonss));
        m_sridLE->setText(QString("%1").arg(m_srid));
    }
}

#include <QDebug>
int CoordWidget::pid() const
{
//    if (m_pid == -1)
//    {
//        int latgg = m_latggLE->text().toInt();
//        int latmm = m_latmmLE->text().toInt();
//        qreal latss = m_latssLE->text().toDouble();

//        int longg = m_longgLE->text().toInt();
//        int lonmm = m_lonmmLE->text().toInt();
//        qreal lonss = m_lonssLE->text().toDouble();

//        qreal lat = static_cast<qreal>(latgg + static_cast<qreal>(latmm) / 60.0 + latss / 60.0 / 60.0);
//        qreal lon = static_cast<qreal>(longg + static_cast<qreal>(lonmm) / 60.0 + lonss / 60.0 / 60.0);


//        QString queryStr = QString("INSERT INTO data.vw_nodes (lat, lon, srid) VALUES (%1, %2, %3)")
//                               .arg(QString::number(lat, 'f', 15))
//                               .arg(QString::number(lon, 'f', 15))
//                               .arg(QString("4740"));
//        QSqlQuery query(queryStr);
//        while (query.next()) {
//        }
//    }

    qDebug() << m_pid << m_latgggLE->text() << m_longggLE->text() << m_sridLE->text();
    return m_pid;
}

void CoordWidget::fieldEdited(const QString &str)
{
    Q_UNUSED(str)

    int latgg = m_latggLE->text().toInt();
    int latmm = m_latmmLE->text().toInt();
    qreal latss = m_latssLE->text().toDouble();

    int longg = m_longgLE->text().toInt();
    int lonmm = m_lonmmLE->text().toInt();
    qreal lonss = m_lonssLE->text().toDouble();

    qreal lat = static_cast<qreal>(latgg + static_cast<qreal>(latmm) / 60.0 + latss / 60.0 / 60.0);
    qreal lon = static_cast<qreal>(longg + static_cast<qreal>(lonmm) / 60.0 + lonss / 60.0 / 60.0);


    m_latgggLE->setText(QString::number(lat, 'f', 15));
    m_longggLE->setText(QString::number(lon, 'f', 15));


    QString queryStr = QString("SELECT lat, lon, srid, note FROM data.vw_node WHERE lat=%1 OR lon=%2")
                                .arg(QString::number(lat, 'f', 15))
                                .arg(QString::number(lon, 'f', 15));

    QSqlQuery query(queryStr);
    QStringList list;
    while (query.next()) {
        QString _lat  = query.value(0).toString();
        QString _lon  = query.value(1).toString();
        QString _srid = query.value(2).toString();
        QString _note = query.value(3).toString();
        QString line = QString("%1   %2   SRID: %3\nNOTE: %4")
                                .arg(GGGtoGGMMSS(query.value(0).toDouble()))
                                .arg(GGGtoGGMMSS(query.value(1).toDouble()))
                                .arg(_srid)
                                .arg(_note);
        list << line;
    }

    QStringListModel * listModel = new QStringListModel();
    listModel->setStringList(list);
    m_listView->setModel(listModel);
}
