#include <QtWidgets>
#include <QtSql>

#include "maindialog.h"
#include "declarations.h"
#include "mapperdialog.h"
#include "tablemodel.h"

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
    m_model = new TableModel();
    m_model->setTable(PGSQL_TABLENAME);
    m_model->setHeaderData(ad_opr,         Qt::Horizontal, trUtf8("OPR"));
    m_model->setHeaderData(ad_country_pid, Qt::Horizontal, trUtf8("Страна"));
    m_model->setHeaderData(ad_cityru,      Qt::Horizontal, trUtf8("Город"));
    m_model->setHeaderData(ad_nameru,      Qt::Horizontal, trUtf8("Наименование"));
    m_model->setHeaderData(ad_name,        Qt::Horizontal, trUtf8("Наименование (eng)"));
    m_model->setHeaderData(ad_indxru,      Qt::Horizontal, trUtf8("Индекс\nИКАО"));
    m_model->setHeaderData(ad_indx,        Qt::Horizontal, trUtf8("Index\nICAO"));
    m_model->setHeaderData(ad_type,        Qt::Horizontal, trUtf8("Тип аэродрома"));
    m_model->setHeaderData(ad_intl,        Qt::Horizontal, trUtf8("INTL"));
    m_model->setHeaderData(ad_department,  Qt::Horizontal, trUtf8("Принадлежность\nк ведомству"));
    m_model->setHeaderData(ad_reglament,   Qt::Horizontal, trUtf8("Регламент\nработы"));
    m_model->setHeaderData(ad_elevation,   Qt::Horizontal, trUtf8("Превышение"));
    m_model->setHeaderData(ad_magvar,      Qt::Horizontal, trUtf8("Магнитное\nсклонение"));
    m_model->setHeaderData(ad_email,       Qt::Horizontal, trUtf8("E-mail"));
    m_model->setHeaderData(ad_web,         Qt::Horizontal, trUtf8("Web-сайт"));
    m_model->setHeaderData(ad_note,        Qt::Horizontal, trUtf8("Примечание"));
    m_model->setHeaderData(ad_geog,        Qt::Horizontal, trUtf8("Координаты"));
    m_model->select();
}

void MainDialog::setupView()
{
    m_view->setModel(m_model);
    m_view->resizeColumnsToContents();
    m_view->horizontalHeader()->setStretchLastSection(true);
    m_view->verticalHeader()->show();
    m_view->hideColumn(ad_pid);
    m_view->hideColumn(ad_reglament);
    m_view->hideColumn(ad_elevation);
    m_view->hideColumn(ad_magvar);
    m_view->hideColumn(ad_email);
    m_view->hideColumn(ad_web);
    m_view->hideColumn(ad_note);
    m_view->hideColumn(ad_geog);
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
    filterDialog_->addColumn(trUtf8("Город"),    "cityru");
    filterDialog_->addColumn(trUtf8("Аэродром"), ad_nameru);
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
