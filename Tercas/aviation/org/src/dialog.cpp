#include "dialog.h"
#include <QtWidgets>
#include <QtSql>

#include "ui_dialog.h"
#include "declarations.h"
#include "tablemodel.h"
#include "imagedelegate.h"
#include "editdialog.h"
#include "emblemdelegate.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);


    m_model = new TableModel(this);
    m_model->setTable("org");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();

    m_model->setHeaderData(org_id,            Qt::Horizontal, trUtf8("ID"));
    m_model->setHeaderData(org_orgRu,         Qt::Horizontal, trUtf8("Название организации"));
    m_model->setHeaderData(org_orgAbridgedRu, Qt::Horizontal, trUtf8("Сокращенное название\nорганизации"));
    m_model->setHeaderData(org_emblem,        Qt::Horizontal, trUtf8("Эмблема"));
    m_model->setHeaderData(org_note,          Qt::Horizontal, trUtf8("Примечание"));


    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->hideColumn(org_id);
    ui->tableView->hideColumn(org_orgAbridgedRu);
    ui->tableView->hideColumn(org_note);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->selectRow(0);
    ui->tableView->setItemDelegateForColumn(org_emblem, new EmblemDelegate);

    ui->tableView->horizontalHeader()->swapSections(org_orgRu, org_emblem);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);


    setWindowTitle(trUtf8("База данных организаций и предприятий"));
}

void Dialog::on_closeButton_clicked()
{
    qApp->quit();
}

void Dialog::on_exportButton_clicked()
{
    QString dirName("/usr/share/vyborg/db/data/aviaDocs/sqlite/emblem/");
    QDir dir(dirName);
    if (!dir.exists(dirName)) {
        dir.mkdir(dirName);
    }

    QSqlDatabase::database().transaction();
    for (int row = 0; row < m_model->rowCount(); row++) {
        QByteArray emblem = m_model->data(m_model->index(row, org_emblem)).toByteArray();
        int id = m_model->data(m_model->index(row, org_id)).toInt();
        QFile file(QString(dirName + QString::number(id)));
        file.open(QFile::WriteOnly);
        file.write(emblem);
        file.close();
    }
    QSqlDatabase::database().commit();
}

void Dialog::on_editButton_clicked()
{
    EditDialog *editDialog = new EditDialog;
    editDialog->setModal(true);
    editDialog->exec();
}
