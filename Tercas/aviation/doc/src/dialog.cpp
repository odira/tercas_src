#include <QtWidgets>
#include <QtSql>

#include "dialog.h"
#include "declarations.h"
#include "aboutdialog.h"
#include "editdialog.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    m_model = new QSqlRelationalTableModel(this);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setTable(MYSQL_TABLE);
    m_model->setRelation(doc_org_id, QSqlRelation("org", "id", "orgRu"));
    m_model->setHeaderData(doc_id,         Qt::Horizontal, trUtf8("ID"));
    m_model->setHeaderData(doc_section_id, Qt::Horizontal, trUtf8("Section ID"));
    m_model->setHeaderData(doc_doc,        Qt::Horizontal, trUtf8("Название документа"));
    m_model->setHeaderData(doc_verNum,     Qt::Horizontal, trUtf8("Редакция\nдокумента"));
    m_model->setHeaderData(doc_verDate,    Qt::Horizontal, trUtf8("Дата редакции\nдокумента"));
    m_model->setHeaderData(doc_org_id,     Qt::Horizontal, trUtf8("Организация"));
    m_model->setHeaderData(doc_issueNum,   Qt::Horizontal, trUtf8("Номер документа\n(Номер приказа)"));
    m_model->setHeaderData(doc_issueDate,  Qt::Horizontal, trUtf8("Дата\nопубликования"));
    m_model->setHeaderData(doc_note,       Qt::Horizontal, trUtf8("Note"));
    m_model->setHeaderData(doc_tags,       Qt::Horizontal, trUtf8("Tags"));
    m_model->select();


    m_view = new QTableView;
    m_view->setModel(m_model);
    m_view->hideColumn(doc_id);
    m_view->hideColumn(doc_section_id);
    m_view->hideColumn(doc_note);
    m_view->hideColumn(doc_tags);

    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->showGrid();
    m_view->setAlternatingRowColors(true);
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->resizeColumnsToContents();
    m_view->horizontalHeader()->setStretchLastSection(true);
    m_view->resizeRowsToContents();
    QHeaderView *verticalHeader = m_view->verticalHeader();
    verticalHeader->setDefaultSectionSize(32);

    m_view->selectRow(0);

    connect(m_view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(on_viewDoubleClicked(QModelIndex)));


    QPushButton *addButton       = new QPushButton(trUtf8("Add document"));
    QPushButton *delButton       = new QPushButton(trUtf8("Delete document"));
    QPushButton *editButton      = new QPushButton(trUtf8("Edit document"));
    QPushButton *exportPdfButton = new QPushButton(trUtf8("Export to pdf..."));
    QPushButton *aboutButton     = new QPushButton(trUtf8("About"));
    QPushButton *closeButton     = new QPushButton(trUtf8("Quit"));

    connect(addButton, SIGNAL(clicked()),
            SLOT(on_addButtonClicked()));
    connect(delButton, SIGNAL(clicked()),
            SLOT(on_delButtonClicked()));
    connect(editButton, SIGNAL(clicked()),
            SLOT(on_editButtonClicked()));
    connect(exportPdfButton, SIGNAL(clicked()),
            SLOT(on_exportPdfButtonClicked()));
    connect(aboutButton, SIGNAL(clicked()),
            SLOT(on_aboutButtonClicked()));
    connect(closeButton, SIGNAL(clicked()),
            qApp, SLOT(quit()));


    QDialogButtonBox *controlButtonBox = new QDialogButtonBox;
    controlButtonBox->setOrientation(Qt::Vertical);
    controlButtonBox->addButton(addButton,       QDialogButtonBox::ActionRole);
    controlButtonBox->addButton(delButton,       QDialogButtonBox::ActionRole);
    controlButtonBox->addButton(editButton,      QDialogButtonBox::ActionRole);
    controlButtonBox->addButton(exportPdfButton, QDialogButtonBox::ActionRole);
    controlButtonBox->addButton(aboutButton,     QDialogButtonBox::ActionRole);
    controlButtonBox->addButton(closeButton,     QDialogButtonBox::ActionRole);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(controlButtonBox);

    setLayout(mainLayout);
}

Dialog::~Dialog()
{
    QFile file("/tmp/test.pdf");
    if (file.exists()) {
        file.remove();
    }
}

void Dialog::on_addButtonClicked()
{
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO docs (doc,org_id) VALUES (:doc,:org_id)");
    query.bindValue(":doc", QString("New Document"));
    query.bindValue(":org_id", QString::number(0));
    query.exec();
    if (query.lastError().isValid()) {
        QMessageBox::warning(this,
                             "Query INSERT error",
                             query.lastError().text());
        QSqlDatabase::database().rollback();
    } else {
        if (!query.isActive()) {
            QMessageBox::warning(this,
                                 "Query LAST_INSERT_ID() function error",
                                 query.lastError().text());
            QSqlDatabase::database().rollback();
        } else {
            query = QSqlQuery("SELECT LAST_INSERT_ID()");
            query.next();
            int id = query.value(0).toInt();

            QSqlDatabase::database().commit();

            m_model->select();

            int count = m_model->rowCount();
            for (int i = 0; i < count; i++) {
                QModelIndex indx = m_model->index(i, 0);
                if (m_model->data(indx).toInt() == id) {
                    m_view->selectRow(indx.row());
                    break;
                }
            }

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,
                                          "Edit Document",
                                          "Открыть новый документ для редактирования?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                on_editButtonClicked();
            }
        }
    }
}

void Dialog::on_delButtonClicked()
{
    int row = m_view->currentIndex().row();
    QModelIndex indx = m_model->index(row, doc_doc);
    QString doc = m_model->data(indx).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Удаление документа",
                                  QString("Удалить документ " + doc + "?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_model->removeRow(row);
        m_model->submitAll();

        m_view->selectRow(0);
    }
}

void Dialog::on_editButtonClicked()
{
    int row = m_view->currentIndex().row();
    QModelIndex indx = m_model->index(row, doc_id);
    int id = m_model->data(indx).toInt();

    EditDialog *dialog = new EditDialog(id, this);
    if (dialog->exec() == QDialog::Accepted) {
        m_model->select();
    }
}

void Dialog::on_exportPdfButtonClicked()
{
    QDir dir("/usr/share/vyborg/db/data/aviaDocs/pdf");
    if (!dir.exists()) {
        qDebug() << "Creating dir for pdf storing";
        dir.mkdir("/usr/share/vyborg/db/data/aviaDocs/pdf");
    }

    QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.prepare("SELECT id, context FROM docs");
    query.exec();
    while (query.next()) {
        int id = query.value("id").toInt();
        QByteArray context = query.value("context").toByteArray();

        QFile file("/usr/share/vyborg/db/data/aviaDocs/pdf/" + QString::number(id) + ".pdf");
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "ERROR: Unable to open file " << id << ".pdf for writing";
            break;
        } else {
            qDebug() << "Writing file " << id << ".pdf";
        }
        file.write(context);
        file.close();
    }

    QSqlDatabase::database().commit();
}

void Dialog::on_aboutButtonClicked()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->exec();
}

void Dialog::on_viewDoubleClicked(QModelIndex index)
{
    int row = index.row();
    QModelIndex indx = m_model->index(row, 0);
    int id = m_model->data(indx).toInt();

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT pdf FROM docsPdf WHERE doc_id=:id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    if (query.lastError().isValid()) {
        qDebug() << "ERROR" << query.lastError().text();
        QSqlDatabase::database().rollback();
    } else {
        QByteArray pdf = query.value(0).toByteArray();
        QSqlDatabase::database().commit();

        QFile file("/tmp/test.pdf");
        if (file.open(QFile::WriteOnly)) {
            file.write(pdf);
            file.close();
//            QDesktopServices::openUrl(QUrl("/tmp/test.pdf"));

            QString prog;

#if defined(Q_OS_ANDROID)
            prog = "/data/data/pdf.reader";
#elif defined(Q_OS_LINUX)
            prog = "/usr/bin/okular";
#endif

            QStringList arguments;
            arguments << "/tmp/test.pdf";

            QProcess pdfProcess;
            pdfProcess.startDetached(prog, arguments);
        }
    }
}
