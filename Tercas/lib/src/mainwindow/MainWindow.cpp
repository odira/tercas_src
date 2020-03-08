#include <QtWidgets>
#include <QtSql>

#include "MainWindow.h"
#include "../maindialogcontrolbuttonbox.h"
#include "../mapperdialog.h"
#include "../filterdialog.h"
#include "../sortdialog.h"
#include "../dialogs/AboutDialog/AboutDialog.h"

//#include "MonthCalendarNavigationToolbar.h"

#include <QDebug>

VyborgMainWindow::VyborgMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_model = new QSqlTableModel(this);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_view = new QTableView(this);
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setShowGrid(true);
    m_view->setAlternatingRowColors(true);
    m_view->verticalHeader()->setVisible(false);
    m_view->setFocus();


    filterDialog_ = new VyborgFilterDialog();
    filterDialog_->setWindowTitle(trUtf8("Filter Dialog"));

    sortDialog_ = new VyborgSortDialog(m_model);
    sortDialog_->setWindowTitle(trUtf8("Sort Dialog"));

    aboutDialog_ = new VyborgAboutDialog;
    aboutDialog_->setWindowTitle(trUtf8("About Dialog"));


    m_controlButtonBox = new VyborgMainDialogControlButtonBox(this);
    m_controlButtonBox->setOrientation(Qt::Vertical);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(m_controlButtonBox);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

//    m_monthCalNavToolBar = new VyborgMonthCalendarNavigationToolbar;
//    addToolBar(m_monthCalNavToolBar);

    connect(m_view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(showMapperDialog()));
    connect(m_controlButtonBox, SIGNAL(filter()),
            SLOT(showFilterDialog()));
    connect(m_controlButtonBox, SIGNAL(sort()),
            SLOT(showSortDialog()));
    connect(m_controlButtonBox, SIGNAL(update()),
            SLOT(update()));
    connect(m_controlButtonBox, SIGNAL(add()),
            SLOT(add()));
    connect(m_controlButtonBox, SIGNAL(remove()),
            SLOT(remove()));
    connect(m_controlButtonBox, SIGNAL(about()),
            SLOT(about()));
    connect(m_controlButtonBox, SIGNAL(close()),
            qApp, SLOT(quit()));
}

QPushButton* VyborgMainWindow::addButton(const QString &text)
{
    return m_controlButtonBox->addButton(text, QDialogButtonBox::ActionRole);
}

void VyborgMainWindow::add()
{
    int val = m_model->insertRow(0);
    if (val == false) {
        QMessageBox::warning(this,
                             trUtf8("Insert New Row"),
                             trUtf8("The database reported an error: %1").arg(m_model->lastError().text()));
        return;
    } else {
        m_view->setCurrentIndex(m_model->index(0, 0));

        m_mapperDialog->setState(VyborgMapperDialog::Add);
        showMapperDialog();
    }
}

void VyborgMainWindow::remove()
{
    QModelIndex viewIndex = m_view->currentIndex();

    int modelRow = viewIndex.row(); // row for model
    int viewRow = viewIndex.row();  // row for view

    QMessageBox msgBox;
    msgBox.setText(trUtf8("WARNING"));
    msgBox.setInformativeText(trUtf8("Are you sure you want to delete the row?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
        m_model->removeRow(modelRow);

        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this,
                                 trUtf8("Commit Changes to Model"),
                                 trUtf8("The database reported an error: %1").arg(m_model->lastError().text()));
        }

        m_view->selectRow(qMin(viewRow, m_model->rowCount()));
    }
}

void VyborgMainWindow::showMapperDialog()
{
    QModelIndex indx = m_view->currentIndex();
    int curRow = indx.row();
    m_mapperDialog->setCurrentRow(curRow);

    m_mapperDialog->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mapperDialog->show();
}

void VyborgMainWindow::showFilterDialog()
{
    int ret = filterDialog_->exec();
    if (ret == QDialog::Accepted)
        m_model->select();
}

void VyborgMainWindow::showSortDialog()
{
    int ret = sortDialog_->exec();
    if (ret == QDialog::Accepted)
        m_model->select();
}

void VyborgMainWindow::update()
{
//    sortFilterProxy_->invalidate();
//    sortFilterProxy_->setFilterWildcard("*");

    m_model->setFilter("");
    m_model->setSort(0, Qt::AscendingOrder);
//    m_model->clear();
    m_model->select();
}

void VyborgMainWindow::about()
{
    aboutDialog_->exec();
}
