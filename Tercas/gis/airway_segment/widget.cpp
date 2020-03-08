#include <QtWidgets>
#include <QtSql>

#include "declarations.h"
#include "widget.h"
#include "relationaltablemodel.h"
#include "mapperdialog.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName("postgres");
    db.setPassword("monrepo");
    db.setDatabaseName("terkas");

    if (!db.open()) {
        qDebug() << "ERROR: Database not opened: " << db.lastError().text();
        return;
    }

    m_model = new RelationalTableModel(this);
    m_model->setTable("terkas.airway_segment");
    m_model->setRelation(col_first_point, QSqlRelation("terkas.point", "id", "label"));
    m_model->setRelation(col_second_point, QSqlRelation("terkas.point", "id", "label"));
    m_model->setRelation(col_airway, QSqlRelation("terkas.airway", "id", "airway"));
    m_model->select();

    m_view = new QTableView;
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_view->setModel(m_model);
    m_view->hideColumn(col_id);
    m_view->hideColumn(col_geom);
    m_view->selectRow(0);

    connect(m_view, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(openMapperDialog(QModelIndex)));


    QPushButton *addButton = new QPushButton(trUtf8("Add"));
    QPushButton *removeButton = new QPushButton(trUtf8("Remove"));
    QPushButton *closeButton = new QPushButton(trUtf8("Close"));

    connect(addButton, SIGNAL(clicked()),
            this, SLOT(add()));
    connect(removeButton, SIGNAL(clicked()),
            this, SLOT(remove()));
    connect(closeButton, SIGNAL(clicked()),
            qApp, SLOT(quit()));

    QDialogButtonBox *bbox = new QDialogButtonBox(Qt::Vertical);
    bbox->addButton(addButton, QDialogButtonBox::ActionRole);
    bbox->addButton(removeButton, QDialogButtonBox::ActionRole);
    bbox->addButton(closeButton, QDialogButtonBox::ActionRole);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(bbox);

    setLayout(mainLayout);
}

void Widget::openMapperDialog(const QModelIndex &indx)
{
    MapperDialog *mapperDialog = new MapperDialog(m_model, indx.row());
    mapperDialog->exec();
}

void Widget::add()
{
    QModelIndex indx = m_view->currentIndex();
    bool ret = m_model->insertRow(indx.row());
    if (ret == true) {
        m_view->setCurrentIndex(indx);
        openMapperDialog(indx);
    }

    m_view->setCurrentIndex(indx);
}

void Widget::remove()
{
    QModelIndex indx = m_view->currentIndex();
    m_model->removeRow(indx.row());
    if (!m_model->submitAll())
        qDebug() << "ERROR: " << m_model->lastError().text();
}
