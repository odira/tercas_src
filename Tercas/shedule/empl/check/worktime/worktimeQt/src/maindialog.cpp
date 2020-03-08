#include <QtWidgets>
#include <QtSql>


#include "maindialog.h"
#include "../model/SectorWorktimeModel.h"
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
    m_model = new SectorWorktimeModel;
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
    m_view->setColumnHidden(SectorWorktimeModel::column_pid, true);
    m_view->setColumnHidden(SectorWorktimeModel::column_personpid, true);
    m_view->setColumnHidden(SectorWorktimeModel::column_sectorpid, true);
    m_view->setColumnHidden(SectorWorktimeModel::column_sectorcolor, true);
    m_view->setColumnHidden(SectorWorktimeModel::column_range, true);
    m_view->setColumnHidden(SectorWorktimeModel::column_startdatetime, true);
    m_view->setColumnHidden(SectorWorktimeModel::column_enddatetime, true);
//    m_view->horizontalHeader()->setStretchLastSection(true);

    m_view->selectRow(0);
}

void MainDialog::setupMapperDialog()
{
    MapperDialog *mapperDialog = new MapperDialog(m_model);
    m_mapperDialog = static_cast<VyborgMapperDialog *>(mapperDialog);
}

void MainDialog::setupFilterDialog()
{
//    filterDialog_->addColumn(trUtf8("Дата"), trUtf8("date"));
//    filterDialog_->addColumn(trUtf8("Внутренние рейсы"), trUtf8("internal"));
//    filterDialog_->addColumn(trUtf8("Международные рейсы"), trUtf8("external"));
//    filterDialog_->addColumn(trUtf8("Транзитные рейсы"), trUtf8("transit"));
//    filterDialog_->addColumn(trUtf8("Рейсы вне расписания (чартерные) рейсы"), trUtf8("charter"));
//    filterDialog_->addColumn(trUtf8("Максимальная суточная интенсивность ВС секторов РДЦ рейсы"), trUtf8("maxday"));
//    filterDialog_->addColumn(trUtf8("Рейсы иностранных авиакомпаний"), trUtf8("foreigner"));
}

void MainDialog::setupSortDialog()
{
//    sortDialog_->addColumn(trUtf8("Дата"), statistics_date);
//    sortDialog_->addColumn(trUtf8("Внутренние рейсы"), statistics_internal);
//    sortDialog_->addColumn(trUtf8("Международные рейсы"), statistics_external);
//    sortDialog_->addColumn(trUtf8("Транзитные рейсы"), statistics_transit);
//    sortDialog_->addColumn(trUtf8("Рейсы вне расписания (чартерные) рейсы"), statistics_charter);
//    sortDialog_->addColumn(trUtf8("Максимальная суточная интенсивность ВС секторов РДЦ рейсы"), statistics_maxday);
//    sortDialog_->addColumn(trUtf8("Рейсы иностранных авиакомпаний"), statistics_foreigner);
}
