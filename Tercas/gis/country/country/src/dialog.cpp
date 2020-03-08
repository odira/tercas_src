#include <QtGui>
#include <QtSql>

#include <QtWidgets>
#include <QTableView>
#include <QHeaderView>

#include "declarations.h"

#include "dialog.h"
#include "tabledelegate.h"
#include "mapperdialog.h"
//#include "sortdialog.h"
//#include "searchdialog.h"

Dialog::Dialog(QWidget *parent) :
    QWidget(parent)
{
    model_ = new QSqlTableModel(this);
    model_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_->setTable(MYSQL_TABLENAME);
    model_->setHeaderData(country_id,              Qt::Horizontal, QObject::trUtf8("ID"));
    model_->setHeaderData(country_name,            Qt::Horizontal, QObject::trUtf8("Country "));
    model_->setHeaderData(country_nameAbridged,    Qt::Horizontal, QObject::trUtf8("Country (Abridged name)"));
    model_->setHeaderData(country_nameRu,         Qt::Horizontal, QObject::trUtf8("Страна"));
    model_->setHeaderData(country_nameAbridgedRu, Qt::Horizontal, QObject::trUtf8("Страна (сокращенное название)"));
    model_->setHeaderData(country_flag,            Qt::Horizontal, QObject::trUtf8("Flag"));
    model_->setHeaderData(country_note,            Qt::Horizontal, QObject::trUtf8("Note"));
    model_->setHeaderData(country_noteRu,         Qt::Horizontal, QObject::trUtf8("Примечание"));
    model_->select();

    view_ = new QTableView;
    view_->setModel(model_);
    view_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view_->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_->setSelectionMode(QAbstractItemView::SingleSelection);
    view_->setShowGrid(true);
    view_->setAlternatingRowColors(true);
    view_->verticalHeader()->setVisible(false);
    view_->horizontalHeader()->setStretchLastSection(true);
    view_->setColumnHidden(country_id,              true);
    view_->setColumnHidden(country_nameAbridged,    true);
    view_->setColumnHidden(country_nameAbridgedRu, true);
    view_->setColumnHidden(country_iso3166_num,     true);
    view_->setColumnHidden(country_iso3166_2,       true);
    view_->setColumnHidden(country_iso3166_3,       true);
    view_->setColumnHidden(country_note,            true);
    view_->setColumnHidden(country_noteRu,         true);
    view_->setItemDelegateForColumn(country_flag, new ImageTableDelegate(view_));
    view_->resizeRowsToContents();
    view_->resizeColumnsToContents();
    view_->setSortingEnabled(true);
    view_->sortByColumn(country_name, Qt::AscendingOrder);
    view_->setFocus();
    view_->selectRow(0);

    QHeaderView *horizontalHeaderView = view_->horizontalHeader();
    horizontalHeaderView->swapSections(country_name, country_nameRu);
    horizontalHeaderView->swapSections(country_flag, country_name);


    resetButton  = new QPushButton(trUtf8("&Reset"));
    addButton    = new QPushButton(trUtf8("&Add"));
    deleteButton = new QPushButton(trUtf8("&Delete"));
    showButton   = new QPushButton(trUtf8("S&how..."));
    sortButton   = new QPushButton(trUtf8("&Sort..."));
    searchButton = new QPushButton(trUtf8("&Find..."));
    closeButton  = new QPushButton(trUtf8("&Close"));

    QDialogButtonBox *dialogButtonBox = new QDialogButtonBox;
    dialogButtonBox->addButton(resetButton,  QDialogButtonBox::ActionRole);
    dialogButtonBox->addButton(addButton,    QDialogButtonBox::ActionRole);
    dialogButtonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);
    dialogButtonBox->addButton(showButton,   QDialogButtonBox::ActionRole);
    dialogButtonBox->addButton(sortButton,   QDialogButtonBox::ActionRole);
    dialogButtonBox->addButton(searchButton, QDialogButtonBox::ActionRole);
    dialogButtonBox->addButton(closeButton,  QDialogButtonBox::ActionRole);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view_);
    mainLayout->addWidget(dialogButtonBox);

    setLayout(mainLayout);
    setWindowTitle(trUtf8("Representation pool of countries and subsidiary territories"));


    connect(view_, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(showMapperDialog()));
    connect(resetButton, SIGNAL(clicked()),
            this, SLOT(reset()));
    connect(addButton, SIGNAL(clicked()),
            this, SLOT(addRow()));
    connect(deleteButton, SIGNAL(clicked()),
            this, SLOT(deleteRow()));
    connect(showButton, SIGNAL(clicked()),
            this, SLOT(showMapperDialog()));
    connect(searchButton, SIGNAL(clicked()),
            this, SLOT(showSearchDialog()));
    connect(sortButton, SIGNAL(clicked()),
            this, SLOT(showSortDialog()));

    connect(closeButton, SIGNAL(clicked()),
            qApp, SLOT(closeAllWindows()));
}

//void Dialog::sort(int column, Qt::SortOrder order, Qt::CaseSensitivity cs)
//{
//    proxy->setSortCaseSensitivity(cs);
//    proxy->sort(column, order);
//}

//void Dialog::search(int column, QRegExp rx, Qt::CaseSensitivity cs)
//{
//    proxy->setFilterCaseSensitivity(cs);
//    proxy->setFilterKeyColumn(column);
//    proxy->setFilterRegExp(rx);
//}

//void Dialog::reset()
//{
//    delete proxy;
//    proxy = new QSortFilterProxyModel(model_);
//    proxy->setSourceModel(model_);

//    view_->setModel(proxy);
//    view_->sortByColumn(country_name, Qt::AscendingOrder);
//    view_->setFocus();
//    view_->selectRow(0);
//}

void Dialog::add()
{
//    int row = 0;
//    model_->insertRow(row);
//    QModelIndex index = proxy->mapFromSource(model_->index(row, 0));

//    MapperDialog dialog(proxy, index.row(), EditState, this);
//    connect(&dialog, SIGNAL(currentRowChanged(int)),
//            view_, SLOT(selectRow(int)));
//    dialog.exec();
}

void Dialog::remove()
{
//    QModelIndex index = view_->currentIndex();
//    int row = index.row();
//    model_->removeRow(row);
//    model_->submitAll();

//    view_->setFocus();
//    view_->selectRow(qMin(row, model_->rowCount()));
}

//void Dialog::showMapperDialog()
//{
//    int row = view_->currentIndex().row();
//    MapperDialog dialog(proxy, row, ShowState, this);
//    connect(&dialog, SIGNAL(currentRowChanged(int)),
//            view_, SLOT(selectRow(int)));
//    dialog.exec();
//}

//void Dialog::showSortDialog()
//{
//    SortDialog *sortDialog = new SortDialog(this);
//    sortDialog->addItem(trUtf8("Country"), country_name);
//    sortDialog->addItem(trUtf8("Country (abridged name)"), country_nameAbridged);
//    sortDialog->addItem(trUtf8("Страна"), country_name_ru);
//    sortDialog->addItem(trUtf8("Страна (сокращенное название)"), country_nameAbridged_ru);
//    connect(sortDialog, SIGNAL(sort(int,Qt::SortOrder,Qt::CaseSensitivity)),
//            this, SLOT(sort(int,Qt::SortOrder,Qt::CaseSensitivity)));
//    sortDialog->exec();
//}

//void Dialog::showSearchDialog()
//{
//    FindDialog *findDialog = new FindDialog(this);
//    findDialog->addItem(trUtf8("Country"), country_name);
//    findDialog->addItem(trUtf8("Country (abridged name)"), country_nameAbridged);
//    findDialog->addItem(trUtf8("Страна"), country_name_ru);
//    findDialog->addItem(trUtf8("Страна (сокращенное название)"), country_nameAbridged_ru);
//    connect(findDialog, SIGNAL(search(int,QRegExp,Qt::CaseSensitivity)),
//            this, SLOT(search(int,QRegExp,Qt::CaseSensitivity)));
//    findDialog->exec();
//}
