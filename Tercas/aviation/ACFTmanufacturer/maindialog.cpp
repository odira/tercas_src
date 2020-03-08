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
    model_->setRelation(ACFTmanufacturer_country_id, QSqlRelation("country.country", "id", "name"));
    model_->select();
}

void MainDialog::setupProxy()
{
    identityProxy_->setSourceModel(model_);
//    identityProxy_->setHeaderData(country_name, Qt::Horizontal, trUtf8("Country Name"));

    sortFilterProxy_->setSourceModel(identityProxy_);
    sortFilterProxy_->sort(ACFTmanufacturer_commonName, Qt::AscendingOrder);
}

void MainDialog::setupView()
{
    view_->setModel(sortFilterProxy_);

    view_->setColumnHidden(ACFTmanufacturer_id, true);

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
    filterDialog_->addColumn(trUtf8("Common Name"), ACFTmanufacturer_commonName);
    filterDialog_->addColumn(trUtf8("Name"), ACFTmanufacturer_name);
    filterDialog_->addColumn(trUtf8("Country"), ACFTmanufacturer_country_id);
}

void MainDialog::setupSortDialog()
{
    sortDialog_->addColumn(trUtf8("Common Name"), ACFTmanufacturer_commonName);
    sortDialog_->addColumn(trUtf8("Name"), ACFTmanufacturer_name);
    sortDialog_->addColumn(trUtf8("Country"), ACFTmanufacturer_country_id);
}
