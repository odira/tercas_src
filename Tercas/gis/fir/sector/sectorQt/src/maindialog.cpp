#include <QtWidgets>
#include <QtSql>

#include "../../model/GisSectorModel.h"
#include "maindialog.h"
#include "mapperdialog.h"

MainDialog::MainDialog(QWidget *parent)
    : VyborgMainDialog(parent)
{
    setupModel();
    setupView();
    setupMapperDialog();
    setupFilterDialog();
    setupSortDialog();

    QLabel *aboutLabel = new QLabel(trUtf8("ABOUT"));
    QVBoxLayout *aboutLayout = new QVBoxLayout;
    aboutLayout->addWidget(aboutLabel);
    aboutDialog_->setLayout(aboutLayout);
}

void MainDialog::setupModel()
{
    m_model = new GisSectorModel;
    m_model->setTable(PGSQL_TABLENAME);
    bool ret = m_model->select();
    if (ret == false) {
        QString msgText("SELECT returned FALSE: " + m_model->lastError().text());
        QMessageBox::warning(this,
                             "ERROR",
                             msgText,
                             QMessageBox::Close);
        qApp->quit();
    }
}

void MainDialog::setupView()
{
    m_view->setModel(m_model);
    m_view->resizeColumnsToContents();
    m_view->verticalHeader()->show();
    m_view->hideColumn(GisSectorModel::Columns::sector_pid);
    m_view->hideColumn(GisSectorModel::Columns::sector_sectorpidarr);
    m_view->hideColumn(GisSectorModel::Columns::sector_border);
    m_view->hideColumn(GisSectorModel::Columns::sector_geog);
    m_view->hideColumn(GisSectorModel::Columns::sector_nodepidarr);
    m_view->hideColumn(GisSectorModel::Columns::sector_color);
    m_view->selectRow(0);
}

void MainDialog::setupMapperDialog()
{
    MapperDialog *mapperDialog = new MapperDialog(m_model, this);
    m_mapperDialog = static_cast<VyborgMapperDialog *>(mapperDialog);
//    m_mapperDialog->resize(800, 480);
}

void MainDialog::setupFilterDialog()
{
    filterDialog_->setModel(m_model);
//    filterDialog_->addColumn(trUtf8("Работник", );
//    filterDialog_->addColumn(trUtf8("ICAO code"), AC_ICAO);
//    filterDialog_->addColumn(trUtf8("IATA code"), AC_IATA);
//    filterDialog_->addColumn(trUtf8("Российский код"), AC_codeRu);
//    filterDialog_->addColumn(trUtf8("Callsign"), AC_CS);
//    filterDialog_->addColumn(trUtf8("Позывной а/к"), AC_CSru);
//    filterDialog_->addColumn(trUtf8("Company name"), AC_AC);
//    filterDialog_->addColumn(trUtf8("Название а/к"), AC_ACru);
//    filterDialog_->addColumn(trUtf8("Страна"), AC_country_id);
}

void MainDialog::setupSortDialog()
{
//    sortDialog_->addColumn(trUtf8("ICAO code"), AC_ICAO);
//    sortDialog_->addColumn(trUtf8("IATA code"), AC_IATA);
//    sortDialog_->addColumn(trUtf8("Российский код"), AC_codeRu);
//    sortDialog_->addColumn(trUtf8("Callsign"), AC_CS);
//    sortDialog_->addColumn(trUtf8("Позывной а/к"), AC_CSru);
//    sortDialog_->addColumn(trUtf8("Company name"), AC_AC);
//    sortDialog_->addColumn(trUtf8("Название а/к"), AC_ACru);
//    sortDialog_->addColumn(trUtf8("Страна"), AC_country_id);
}
