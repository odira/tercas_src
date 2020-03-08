#include <QtWidgets>
#include <QtSql>

#include "../model/NodeTableModel.h"
#include "maindialog.h"
#include "mapperdialog.h"
//#include "NodeDialog.h"

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
//    NodeTableModel *tmpModel = new NodeTableModel;
//    m_model = qobject_cast < QSqlTableModel * > (tmpModel);

    m_model = new NodeTableModel;
//    m_model->setTable(PGSQL_TABLENAME);
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
    m_view->horizontalHeader()->setStretchLastSection(true);
//    m_view->hideColumn(NodeTableModel::Columns::column_pid);
    m_view->hideColumn(NodeTableModel::Columns::column_geog);

    m_view->selectRow(0);
}

void MainDialog::setupMapperDialog()
{
    MapperDialog * mapperDialog = new MapperDialog(m_model, this);
    m_mapperDialog = static_cast < VyborgMapperDialog * > (mapperDialog);
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
