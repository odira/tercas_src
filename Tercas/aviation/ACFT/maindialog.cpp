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
    model_->select();
}

void MainDialog::setupProxy()
{
    identityProxy_->setSourceModel(model_);
    identityProxy_->setHeaderData(ACFT_id, Qt::Horizontal, trUtf8("ID"));

    sortFilterProxy_->setSourceModel(identityProxy_);
    sortFilterProxy_->sort(ACFT_type, Qt::AscendingOrder);
}


void MainDialog::setupView()
{
    view_->setModel(sortFilterProxy_);

    view_->setColumnHidden(ACFT_id, true);

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
    filterDialog_->addColumn(trUtf8("Type"), ACFT_type);
    filterDialog_->addColumn(trUtf8("Designator"), ACFT_designator);
}

void MainDialog::setupSortDialog()
{
    sortDialog_->addColumn(trUtf8("Type"), ACFT_type);
    sortDialog_->addColumn(trUtf8("Designator"), ACFT_designator);
}
