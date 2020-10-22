#include <QtWidgets>
#include <QtSql>

#include "EmplSheduleIntervalModel.h"
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
}

void MainDialog::setupModel()
{
    EmplSheduleIntervalModel *model_ = new EmplSheduleIntervalModel;
    m_model =  static_cast < QSqlTableModel* > (model_);
}

void MainDialog::setupView()
{
    m_view->setModel(m_model);
    m_view->resizeColumnsToContents();

    m_view->setColumnHidden(EmplSheduleIntervalModel::Columns::column_pid, true);
    m_view->setColumnHidden(EmplSheduleIntervalModel::Columns::column_person_pid, true);
    m_view->setColumnHidden(EmplSheduleIntervalModel::Columns::column_person_shift_num, true);
    m_view->setColumnHidden(EmplSheduleIntervalModel::Columns::column_activity_pid, true);
    m_view->setColumnHidden(EmplSheduleIntervalModel::Columns::column_activity_color, true);
    m_view->setColumnHidden(EmplSheduleIntervalModel::Columns::column_activity_note, true);
    m_view->horizontalHeader()->setStretchLastSection(true);

    m_view->selectRow(0);
}

void MainDialog::setupMapperDialog()
{
    MapperDialog *mapperDialog = new MapperDialog(m_model);
    m_mapperDialog = static_cast<VyborgMapperDialog *>(mapperDialog);
//    m_mapperDialog->setModal(true);
}

void MainDialog::setupFilterDialog()
{
    filterDialog_->setModel(m_model);
    filterDialog_->addColumn(tr("Работник"), tr("person_full_name"));
}

void MainDialog::setupSortDialog()
{
//    sortDialog_->addColumn(trUtf8("Дата"), statistics_date);
}
