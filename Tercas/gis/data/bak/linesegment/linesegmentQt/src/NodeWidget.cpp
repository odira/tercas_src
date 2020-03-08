#include <QtWidgets>
#include <QtSql>

#include "NodeWidget.h"

NodeWidget::NodeWidget(QWidget *parent)
    : QWidget(parent),
      m_nodepid(-1)
{
    m_nodepidSB = new QSpinBox;
    m_nodepidSB->setRange(0, 1000);

    /*  Widgets
     */
    m_latLineEdit  = new QLineEdit;
    m_latLineEdit->setAlignment(Qt::AlignRight);
    m_lonLineEdit  = new QLineEdit;
    m_lonLineEdit->setAlignment(Qt::AlignRight);
    m_sridLineEdit = new QLineEdit;
    m_sridLineEdit->setAlignment(Qt::AlignRight);

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


    /*  Coordinate Radio Button Group
     */
    m_radioButton1 = new QRadioButton(trUtf8("град° (ггг.ггггг°)"));
    m_radioButton2 = new QRadioButton(trUtf8("град° мин\' сек\" (ггг° мм\' сс.ссс\")"));

    QButtonGroup *buttonGroup = new QButtonGroup;
    buttonGroup->addButton(m_radioButton1);
    buttonGroup->addButton(m_radioButton2);
    m_radioButton1->setChecked(true);

    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(update()));

    QVBoxLayout *radioButtonBox = new QVBoxLayout;
    radioButtonBox->addWidget(m_radioButton1);
    radioButtonBox->addWidget(m_radioButton2);


    m_nodenoteruPTE = new QPlainTextEdit;


    QVBoxLayout *innerLayout = new QVBoxLayout;
    innerLayout->addWidget(m_nodepidSB);
    innerLayout->addLayout(coordLayout);
    innerLayout->addLayout(radioButtonBox);
    innerLayout->addWidget(m_nodenoteruPTE);

    QGroupBox *m_groupBox = new QGroupBox;
    m_groupBox->setTitle(trUtf8("Координаты точки"));
    m_groupBox->setLayout(innerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(mainLayout);
}

void NodeWidget::setNodepid(const int &nodepid)
{
    if (nodepid != m_nodepid) {
        m_nodepid = nodepid;
        emit nodepidChanged(m_nodepid);
        update();
    }
}

//QString NodeWidget::geog() const
//{
//    QString lat;
//    QString lon;

//    if (m_radioButton1->isChecked())
//    {
//        lat = m_latLineEdit->text().mid(0, 8);
//        lon = m_lonLineEdit->text().mid(0, 9);
//    }
//    else if (m_radioButton2->isChecked())
//    {
//        QString _lat = m_latLineEdit->text();
//        QString _lon = m_lonLineEdit->text();

//        QString lat_gg = _lat.mid(0, 2);
//        QString lat_mm = _lat.mid(4, 2);
//        QString lat_ss = _lat.mid(8, 6);

//        QString lon_gg = _lon.mid(0, 3);
//        QString lon_mm = _lon.mid(5, 2);
//        QString lon_ss = _lon.mid(9, 6);

//        QString tmp1 = lat_gg + "°" + lat_mm + "''" + lat_ss;
//        QString tmp2 = lon_gg + "°" + lon_mm + "''" + lon_ss;

//        QString queryString = QString("SELECT func.f_dms2dd('%1'),func.f_dms2dd('%2')").arg(tmp1).arg(tmp2);
//        QSqlQuery query(queryString);
//        while (query.next()) {
//            lat = query.value(0).toString();
//            lon = query.value(1).toString();
//        }
//        query.clear();
//    }

//    QString queryString = QString("SELECT ST_GeographyFromText('SRID=4326;POINT(%1 %2)')")
//            .arg(lon)
//            .arg(lat);
//    QSqlQuery query(queryString);
//    while (query.next()) {
//        m_geog = query.value(0).toString();
//    }
//    query.clear();

//    return m_geog;
//}

int NodeWidget::nodepid()
{
    m_nodepid = m_nodepidSB->value();
    return m_nodepid;
}

void NodeWidget::setEnabled(bool state)
{
    if (state == true) {
        m_nodepidSB->setReadOnly(false);
        m_latLineEdit->setReadOnly(false);
        m_lonLineEdit->setReadOnly(false);
        m_sridLineEdit->setReadOnly(false);
        m_nodenoteruPTE->setReadOnly(false);
    } else {
        m_nodepidSB->setReadOnly(true);
        m_latLineEdit->setReadOnly(true);
        m_lonLineEdit->setReadOnly(true);
        m_sridLineEdit->setReadOnly(true);
        m_nodenoteruPTE->setReadOnly(true);
    }
}

//void NodeWidget::coordEdited(const QString &text)
//{
//    Q_UNUSED(text)

//    QString coord = this->geog();

//    QString queryString = QString("SELECT true FROM data.node WHERE geog='%1'").arg(coord);
//    QSqlQuery query(queryString);
//    while (query.next()) {
//        if (query.value(0).toBool() == true) {
//            QMessageBox msgBox;
//            msgBox.setText("NODE with the same coordinates already EXISTS!");
//            msgBox.exec();

//            emit geogFound(coord);
//        }
//    }
//}

#include <QDebug>
void NodeWidget::update()
{
    // If not running QPSQL driver start new one
    if (!QSqlDatabase::contains()) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setUserName("postgres");
        db.setPassword("monrepo");
        db.setDatabaseName("gis");
        db.open();
    }

    int nodepid;
    QStringList coord;
    QString lat;
    QString lon;
    QString srid;
    QString queryString;
    QString nodenoteru;

    if (m_radioButton1->isChecked())
    {
        queryString = QString("SELECT pid, St_AsLatLonText(geog::geometry,'D.DDDDDDDDDD'), St_SRID(geog::geometry), noteru "
                              "FROM data.vw_node "
                              "WHERE pid=%1")
                .arg(m_nodepid);
        QSqlQuery query(queryString);
        while (query.next()) {
            nodepid = query.value(0).toInt();

            coord = query.value(1).toString().split(" ");
            lat = coord.at(0);
            lon = coord.at(1);
            if (lon.length() <= 13)
                lon.prepend("0");

            srid = query.value(2).toString();

            nodenoteru = query.value(3).toString();
        }
        query.clear();

        m_latLineEdit->setInputMask(QString("99.9999999999°;_"));
        m_lonLineEdit->setInputMask(QString("999.9999999999°;_"));
    }
    else
    {
        queryString = QString("SELECT pid, St_AsLatLonText(geog::geometry, 'D M S.SSS'), St_SRID(geog::geometry), noteru "
                              "FROM data.vw_node "
                              "WHERE pid=%1")
                .arg(m_nodepid);
        QSqlQuery query(queryString);
        while (query.next()) {
            nodepid = query.value(0).toInt();

            coord = query.value(1).toString().split(" ");

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

            srid = query.value(2).toString();

            nodenoteru = query.value(3).toString();
        }
        query.clear();

        m_latLineEdit->setInputMask(QString("99° 99\' 99.999\";_"));
        m_lonLineEdit->setInputMask(QString("999° 99\' 99.999\";_"));
    }

    m_nodepidSB->clear();
    m_latLineEdit->clear();
    m_lonLineEdit->clear();
    m_sridLineEdit->clear();
    m_nodenoteruPTE->clear();

    m_nodepidSB->setValue(nodepid);
    m_latLineEdit->setText(lat);
    m_lonLineEdit->setText(lon);
    m_sridLineEdit->setText(srid);
    m_nodenoteruPTE->setPlainText(nodenoteru);
}
