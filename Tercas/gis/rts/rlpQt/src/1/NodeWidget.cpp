#include <QtWidgets>
#include <QtSql>

#include "NodeWidget.h"

NodeWidget::NodeWidget(QWidget *parent)
    : QWidget(parent),
      m_geog(QString())
{
    m_latLineEdit  = new QLineEdit;
    m_latLineEdit->setAlignment(Qt::AlignRight);
    m_lonLineEdit  = new QLineEdit;
    m_lonLineEdit->setAlignment(Qt::AlignRight);
    m_sridLineEdit = new QLineEdit;
    m_sridLineEdit->setAlignment(Qt::AlignRight);

    connect(m_latLineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(coordEdited(QString)));
    connect(m_lonLineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(coordEdited(QString)));

    QGridLayout *coordLayout = new QGridLayout;
    coordLayout->setHorizontalSpacing(0);
    coordLayout->addWidget(new QLabel(trUtf8("Широта")), 0, 0);
    coordLayout->addWidget(new QLabel(trUtf8("Долгота")), 0, 1);
    coordLayout->addWidget(new QLabel(trUtf8("SRID")), 0, 2);
    coordLayout->addWidget(m_latLineEdit, 1, 0);
    coordLayout->setColumnMinimumWidth(0, 150);
    coordLayout->addWidget(m_lonLineEdit, 1, 1);
    coordLayout->setColumnMinimumWidth(1, 150);
    coordLayout->addWidget(m_sridLineEdit, 1, 2);
    coordLayout->setColumnMinimumWidth(2, 50);
    coordLayout->setColumnStretch(2, 0);

    m_radioButton1 = new QRadioButton(trUtf8("град° (ггг.ггггг°)"));
    m_radioButton1->setChecked(true);
    m_radioButton2 = new QRadioButton(trUtf8("град° мин\' сек\" (ггг° мм\' сс.ссс\")"));

    QButtonGroup *buttonGroup = new QButtonGroup;
    buttonGroup->addButton(m_radioButton1);
    buttonGroup->addButton(m_radioButton2);

    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(update()));

    QVBoxLayout *radioButtonBox = new QVBoxLayout;
    radioButtonBox->addWidget(m_radioButton1);
    radioButtonBox->addWidget(m_radioButton2);

    QVBoxLayout *innerLayout = new QVBoxLayout;
    innerLayout->addLayout(coordLayout);
    innerLayout->addLayout(radioButtonBox);

    QGroupBox *m_groupBox = new QGroupBox;
    m_groupBox->setTitle(trUtf8("Координаты точки"));
    m_groupBox->setLayout(innerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(mainLayout);

    setEnabled(false);
}

void NodeWidget::setGeog(const QString &geog)
{
    if (geog != m_geog) {
        m_geog = geog;
        emit geogChanged();
        update();
    }
}

QString NodeWidget::geog() const
{
    QString lat;
    QString lon;

    if (m_radioButton1->isChecked())
    {
        lat = m_latLineEdit->text().mid(0, 8);
        lon = m_lonLineEdit->text().mid(0, 9);
    }
    else if (m_radioButton2->isChecked())
    {
        QString _lat = m_latLineEdit->text();
        QString _lon = m_lonLineEdit->text();

        QString lat_gg = _lat.mid(0, 2);
        QString lat_mm = _lat.mid(4, 2);
        QString lat_ss = _lat.mid(8, 6);

        QString lon_gg = _lon.mid(0, 3);
        QString lon_mm = _lon.mid(5, 2);
        QString lon_ss = _lon.mid(9, 6);

        QString tmp1 = lat_gg + "°" + lat_mm + "''" + lat_ss;
        QString tmp2 = lon_gg + "°" + lon_mm + "''" + lon_ss;

        QString queryString = QString("SELECT func.f_dms2dd('%1'),func.f_dms2dd('%2')").arg(tmp1).arg(tmp2);
        QSqlQuery query(queryString);
        while (query.next()) {
            lat = query.value(0).toString();
            lon = query.value(1).toString();
        }
        query.clear();
    }

    QString queryString = QString("SELECT ST_GeographyFromText('SRID=4326;POINT(%1 %2)')")
            .arg(lon)
            .arg(lat);
    QSqlQuery query(queryString);
    while (query.next()) {
        m_geog = query.value(0).toString();
    }
    query.clear();

    return m_geog;
}

void NodeWidget::setEnabled(bool state)
{
    if (state == true) {
        m_latLineEdit->setReadOnly(false);
        m_lonLineEdit->setReadOnly(false);
        m_sridLineEdit->setReadOnly(false);
    } else {
        m_latLineEdit->setReadOnly(true);
        m_lonLineEdit->setReadOnly(true);
        m_sridLineEdit->setReadOnly(true);
    }
}

void NodeWidget::coordEdited(const QString &text)
{
    Q_UNUSED(text)

    QString coord = this->geog();

    QString queryString = QString("SELECT true FROM data.node WHERE geog='%1'").arg(coord);
    QSqlQuery query(queryString);
    while (query.next()) {
        if (query.value(0).toBool() == true) {
            QMessageBox msgBox;
            msgBox.setText("NODE with the same coordinates already EXISTS!");
            msgBox.exec();

            emit geogFound(coord);
        }
    }
}

void NodeWidget::update()
{
    // if not running QPSQL driver start new one
    if (!QSqlDatabase::contains()) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setUserName("postgres");
        db.setPassword("monrepo");
        db.setDatabaseName("gis");
        db.open();
    }

    if (m_radioButton1->isChecked())
    {
        m_latLineEdit->setInputMask(QString("99.9999999999°;_"));
        m_lonLineEdit->setInputMask(QString("999.9999999999°;_"));

        if (m_geog.isEmpty()) {
            // input nothing into lineEdit's
            m_latLineEdit->setText(QString());
            m_lonLineEdit->setText(QString());
            m_sridLineEdit->setText(QString());
        } else {
            QStringList coord;
            QString lat;
            QString lon;
            QString srid;

            QString queryString = QString("SELECT St_AsLatLonText('%1'::geometry,'D.DDDDDDDDDD'),St_SRID('%1'::geometry)")
                    .arg(m_geog);
            QSqlQuery query(queryString);
            while (query.next()) {
                coord = query.value(0).toString().split(" ");
                lat = coord.at(0);
                lon = coord.at(1);
//                qDebug() << QString::number(lon, 'f', 25);
                if (lon.length() == 13)
                    lon.prepend("0");
                srid = query.value(1).toString();
            }
            query.clear();

            m_latLineEdit->setText(lat);
            m_lonLineEdit->setText(lon);
            m_sridLineEdit->setText(srid);
        }
    }
    else if (m_radioButton2->isChecked())
    {
        m_latLineEdit->setInputMask(QString("99° 99\' 99.999\";_"));
        m_lonLineEdit->setInputMask(QString("999° 99\' 99.999\";_"));

        if (m_geog.isEmpty())
        {
            // input nothing into lineEdit's
            m_latLineEdit->setText(QString());
            m_lonLineEdit->setText(QString());
            m_sridLineEdit->setText(QString());
        }
        else
        {
            QStringList coord;
            QString lat;
            QString lon;
            QString srid;

            QString queryString = QString("SELECT St_AsLatLonText('%1'::geometry, 'D M S.SSS'),St_SRID('%1'::geometry)")
                                          .arg(m_geog);
            QSqlQuery query(queryString);
            while (query.next()) {
                coord = query.value(0).toString().split(" ");

                QString lat_gg = coord.at(0);
                if (lat_gg.length() == 1)
                    lat_gg.prepend("0");
                QString lat_mm = coord.at(1);
                if (lat_mm.length() == 1)
                    lat_mm.prepend("0");
                QString lat_ss = coord.at(2);
                if (lat_ss.length() == 5)
                    lat_ss.prepend("0");

                QString lon_gg = coord.at(3);
                if (lon_gg.length() == 1)
                    lon_gg.prepend("0");
                if (lon_gg.length() == 2)
                    lon_gg.prepend("0");
                QString lon_mm = coord.at(4);
                if (lon_mm.length() == 1)
                    lon_mm.prepend("0");
                QString lon_ss = coord.at(5);
                if (lon_ss.length() == 5)
                    lon_ss.prepend("0");

                lat = lat_gg + lat_mm + lat_ss;
                lon = lon_gg + lon_mm + lon_ss;

                srid = query.value(1).toString();
            }
            query.clear();

            m_latLineEdit->setText(lat);
            m_lonLineEdit->setText(lon);
            m_sridLineEdit->setText(srid);
        }
    }

    m_latLineEdit->setCursorPosition(0);
//    m_latLineEdit->setFocus();
}

