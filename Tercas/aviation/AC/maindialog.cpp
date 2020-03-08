#include <QtWidgets>
#include <QtSql>

#include "maindialog.h"
#include "declarations.h"
#include "mapperdialog.h"



MainDialog::MainDialog(QWidget *parent)
    : VyborgMainDialog(parent)
{
    setupModel();
    setupProxy();
    setupView();
    setupMapperDialog();
    setupFilterDialog();
    setupSortDialog();
}

void MainDialog::setupModel()
{
    model_->setTable(MYSQL_TABLENAME);
    model_->setRelation(AC_country_id, QSqlRelation("country.country", "id", "name"));
    model_->select();
}

void MainDialog::setupProxy()
{
    identityProxy_->setSourceModel(model_);
    identityProxy_->setHeaderData(AC_id, Qt::Horizontal, trUtf8("ID"));

    sortFilterProxy_->setSourceModel(identityProxy_);
    sortFilterProxy_->sort(AC_AC, Qt::AscendingOrder);
}

void MainDialog::setupView()
{
    view_->setModel(sortFilterProxy_);

    view_->setColumnHidden(AC_id, true);

    view_->resizeRowsToContents();
    view_->resizeColumnsToContents();

    view_->selectRow(0);
}

void MainDialog::setupMapperDialog()
{
    MapperDialog *mapperDialog = new MapperDialog(sortFilterProxy_, this);
    mapperDialog_ = static_cast<VyborgMapperDialog *>(mapperDialog);
}

void MainDialog::setupFilterDialog()
{
    filterDialog_->addColumn(trUtf8("ICAO code"), AC_ICAO);
    filterDialog_->addColumn(trUtf8("IATA code"), AC_IATA);
    filterDialog_->addColumn(trUtf8("Российский код"), AC_codeRu);
    filterDialog_->addColumn(trUtf8("Callsign"), AC_CS);
    filterDialog_->addColumn(trUtf8("Позывной а/к"), AC_CSru);
    filterDialog_->addColumn(trUtf8("Company name"), AC_AC);
    filterDialog_->addColumn(trUtf8("Название а/к"), AC_ACru);
    filterDialog_->addColumn(trUtf8("Страна"), AC_country_id);
}

void MainDialog::setupSortDialog()
{
    sortDialog_->addColumn(trUtf8("ICAO code"), AC_ICAO);
    sortDialog_->addColumn(trUtf8("IATA code"), AC_IATA);
    sortDialog_->addColumn(trUtf8("Российский код"), AC_codeRu);
    sortDialog_->addColumn(trUtf8("Callsign"), AC_CS);
    sortDialog_->addColumn(trUtf8("Позывной а/к"), AC_CSru);
    sortDialog_->addColumn(trUtf8("Company name"), AC_AC);
    sortDialog_->addColumn(trUtf8("Название а/к"), AC_ACru);
    sortDialog_->addColumn(trUtf8("Страна"), AC_country_id);
}
