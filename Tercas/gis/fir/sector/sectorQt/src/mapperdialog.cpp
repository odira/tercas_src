#include <QtWidgets>
#include <QtSql>

#include "../../model/GisSectorModel.h"

#include "mapperdialog.h"
#include "mapperdelegate.h"
#include "NodePidArrayTableWidget.h"
#include "SectorPidArrayWidget.h"
#include "ColorWidget.h"

MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_pidLE = new QLineEdit;
    m_sectorpidarrW = new SectorPidArrayWidget;
    m_nameLE = new QLineEdit;
    m_compoundCB = new QCheckBox(trUtf8("Совмещенный сектор"));
    m_compoundCB->setEnabled(false);
    m_freqLE = new QLineEdit;
    m_nodeArrayW = new NodePidArrayTableWidget;
    m_phoneLE = new QLineEdit;
    m_npsdzLE = new QLineEdit;
    m_npspdzLE = new QLineEdit;
    m_colorW = new ColorWidget;


    QDataWidgetMapper* m_mapper = mapper();

    m_mapper->addMapping(m_pidLE, GisSectorModel::sector_pid);
    m_mapper->addMapping(m_sectorpidarrW, GisSectorModel::sector_sectorpidarr, "array");
    m_mapper->addMapping(m_nameLE, GisSectorModel::sector_name);
    m_mapper->addMapping(m_compoundCB, GisSectorModel::sector_compound);
    m_mapper->addMapping(m_freqLE, GisSectorModel::sector_freq);
//    m_mapper->addMapping(m_nodeArrayW, sector_nodepidarr, "nodepidarr");
    m_mapper->addMapping(m_phoneLE, GisSectorModel::sector_phone);
    m_mapper->addMapping(m_npsdzLE, GisSectorModel::sector_npsdz);
    m_mapper->addMapping(m_npspdzLE, GisSectorModel::sector_npspdz);
    m_mapper->addMapping(m_colorW, GisSectorModel::sector_color);

//    m_mapper->setItemDelegate(new MapperDelegate);
}

void MapperDialog::layoutPrivateWidgets()
{
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_compoundCB, 1, 1);
    gridLayout->addWidget(new QLabel(trUtf8("Обозначение")), 3, 0);
    gridLayout->addWidget(m_sectorpidarrW, 3, 1);
    gridLayout->addWidget(new QLabel(trUtf8("Полное наименование")), 4, 0);
    gridLayout->addWidget(m_nameLE, 4, 1);
    gridLayout->addWidget(new QLabel(trUtf8("Частота сектора")), 5, 0);
    gridLayout->addWidget(m_freqLE, 5, 1);

    QHBoxLayout *hPhoneLayout = new QHBoxLayout;
    hPhoneLayout->addWidget(m_phoneLE);

    QGroupBox *phoneBox = new QGroupBox(trUtf8("Телефоны"));
    phoneBox->setLayout(hPhoneLayout);

    QHBoxLayout *hNpsLayout = new QHBoxLayout;
    hNpsLayout->addWidget(m_npsdzLE);
    hNpsLayout->addWidget(m_npspdzLE);

    QGroupBox *npsBox = new QGroupBox(trUtf8("НПС (Нормативы пропускной способности)"));
    npsBox->setLayout(hNpsLayout);


    QHBoxLayout *colorWLayout = new QHBoxLayout;
    colorWLayout->addWidget(m_colorW);
    colorWLayout->addStretch(1);

    QVBoxLayout *tabLayout1 = new QVBoxLayout;
    tabLayout1->addWidget(phoneBox);
    tabLayout1->addWidget(npsBox);
    tabLayout1->addLayout(colorWLayout);
    tabLayout1->addStretch(1);

    QWidget *tab1 = new QWidget;
    tab1->setLayout(tabLayout1);


    QWidget *tab2 = new QWidget;

    QVBoxLayout *tabLayout2 = new QVBoxLayout;
    tab2->setLayout(tabLayout2);

    tabLayout2->addWidget(m_nodeArrayW);


    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab(tab1, trUtf8("Общая информация"));
    tabWidget->addTab(tab2, trUtf8("Граница"));

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(gridLayout);
    privateWidgetsLayout->addWidget(tabWidget);
}

void MapperDialog::updatePrivateWidgets()
{
    if (state() == Edit)
    {
        m_pidLE->setReadOnly(false);
        m_sectorpidarrW->setEnabled(true);
        m_nameLE->setReadOnly(false);
        m_compoundCB->setEnabled(true);
        m_freqLE->setReadOnly(false);
        m_nodeArrayW->setEnabled(true);
        m_phoneLE->setReadOnly(false);
        m_npsdzLE->setReadOnly(false);
        m_npspdzLE->setReadOnly(false);
        m_colorW->setEnabled(true);
    }
    else
    {
        m_pidLE->setReadOnly(true);
        m_sectorpidarrW->setEnabled(false);
        m_nameLE->setReadOnly(true);
        m_compoundCB->setEnabled(false);
        m_freqLE->setReadOnly(true);
        m_nodeArrayW->setEnabled(false);
        m_phoneLE->setReadOnly(true);
        m_npsdzLE->setReadOnly(true);
        m_npspdzLE->setReadOnly(true);
        m_colorW->setEnabled(false);
    }
}

