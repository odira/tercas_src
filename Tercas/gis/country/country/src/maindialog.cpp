#include <QtWidgets>
#include <QtSql>

#include "maindialog.h"
#include "declarations.h"
#include "mapperdialog.h"


MainDialog::MainDialog(QWidget *parent)
    : VyborgMainDialog(parent)
{
    setupModel();
    setupView();
    setupMapperDialog();
    setupFilterDialog();
    setupSortDialog();
}

void MainDialog::setupModel()
{
    m_model->setTable(PGSQL_TABLENAME);
    m_model->select();

    m_model->setHeaderData(country_pid,          Qt::Horizontal, trUtf8("ID"));
    m_model->setHeaderData(country_name,         Qt::Horizontal, trUtf8("Country"));
    m_model->setHeaderData(country_nameru,       Qt::Horizontal, trUtf8("Страна"));
    m_model->setHeaderData(country_nameshort,    Qt::Horizontal, trUtf8("Country\n(Abridged name)"));
    m_model->setHeaderData(country_nameshortru,  Qt::Horizontal, trUtf8("Страна\n(Сокращенное название)"));
    m_model->setHeaderData(country_iso3166code2, Qt::Horizontal, trUtf8("Код ISO3166 2"));
    m_model->setHeaderData(country_iso3166code3, Qt::Horizontal, trUtf8("Код ISO3166 3"));
    m_model->setHeaderData(country_iso3166coden, Qt::Horizontal, trUtf8("Код ISO3166 num"));
    m_model->setHeaderData(country_note,         Qt::Horizontal, trUtf8("Note"));
    m_model->setHeaderData(country_noteru,       Qt::Horizontal, trUtf8("Примечание"));
    m_model->setHeaderData(country_geog,         Qt::Horizontal, trUtf8("Координаты"));
}

void MainDialog::setupView()
{
    m_view->setModel(m_model);
//    m_view->setItemDelegate(new PersonModelDelegate(m_view));

    m_view->resizeColumnsToContents();
//    m_view->resizeRowsToContents();
    m_view->horizontalHeader()->setStretchLastSection(true);

    m_view->verticalHeader()->show();

    m_view->hideColumn(country_pid);
    m_view->hideColumn(country_note);
    m_view->hideColumn(country_noteru);
    m_view->hideColumn(country_geog);

    m_view->selectRow(0);
}

void MainDialog::setupMapperDialog()
{
    MapperDialog *mapperDialog = new MapperDialog(m_model, this);
    m_mapperDialog = static_cast<VyborgMapperDialog *>(mapperDialog);
    m_mapperDialog->resize(800, 480);
}

void MainDialog::setupFilterDialog()
{
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
