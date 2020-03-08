#include <QtWidgets>
#include <QtSql>

#include "editdialog.h"
#include "declarations.h"
#include "orgdialog.h"

#include <QDebug>


EditDialog::EditDialog(int id, QWidget *parent)
    : QDialog(parent), m_id(id)
{
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.prepare("SELECT doc.*, org.orgRu "
                  "FROM doc LEFT JOIN org ON doc.org_id=org.id "
                  "WHERE doc.id=:id");
    query.bindValue(":id", m_id);
    query.exec();
    query.next();
    if (query.lastError().isValid()) {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        return;
    }

    QString doc       = query.value(doc_doc).toString();
    QString version   = query.value(doc_verDate).toString();
    QString issueNum  = query.value(doc_issueNum).toString();
    QDate   issueDate = query.value(doc_issueDate).toDate();
    QString note      = query.value(doc_note).toString();
    QString tags      = query.value(doc_tags).toString();
    QString org       = query.value(org_orgRu).toString();


    QSqlDatabase::database().commit();


    m_docLineEdit       = new QLineEdit;
    m_versionLineEdit   = new QLineEdit;
    m_orgLineEdit       = new QLineEdit;
    m_issueNumLineEdit  = new QLineEdit;
    m_issueDateEdit     = new QDateEdit;
    m_noteTextEdit      = new QTextEdit;
    m_tagsLineEdit      = new QLineEdit;

    m_docLineEdit->setText(doc);
    m_versionLineEdit->setText(version);
    m_orgLineEdit->setText(org);
    m_issueNumLineEdit->setText(issueNum);
    m_issueDateEdit->setDate(issueDate);
    m_issueDateEdit->setDisplayFormat("dd MMMM yyyy");
    m_noteTextEdit->setText(note);
    m_tagsLineEdit->setText(tags);

    QPushButton *addOrgButton = new QPushButton(trUtf8("Select..."));
    connect(addOrgButton, SIGNAL(clicked()),
            SLOT(on_addOrgButtonClicked()));

    QHBoxLayout *addOrgLayout = new QHBoxLayout;
    addOrgLayout->addWidget(m_orgLineEdit);
    addOrgLayout->addWidget(addOrgButton);



    QPushButton *fileButton = new QPushButton(trUtf8("Select File"));
    QPushButton *sqliteButton = new QPushButton (trUtf8("Export to sqlite"));
//    if (context == 0) {
//        fileButton->setText(trUtf8("NO CONTEXT"));
//        sqliteButton->setText(trUtf8("No context to export"));
//    }

    connect(fileButton, SIGNAL(clicked()),
            SLOT(on_fileButtonClicked()));
    connect(sqliteButton, SIGNAL(clicked()),
            SLOT(on_sqliteButtonClicked()));

    QFrame *frame = new QFrame;
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QFormLayout *formLayout = new QFormLayout(frame);
    formLayout->addRow(trUtf8("Document:"),    m_docLineEdit);
    formLayout->addRow(trUtf8("Revision"),     m_versionLineEdit);
    formLayout->addRow(trUtf8("Organization"), addOrgLayout);
    formLayout->addRow(trUtf8("Issue:"),       m_issueNumLineEdit);
    formLayout->addRow(trUtf8("Issue Date"),   m_issueDateEdit);
    formLayout->addRow(trUtf8("Tags:"),        m_tagsLineEdit);
    formLayout->addRow(trUtf8("Note"),         m_noteTextEdit);
    formLayout->addRow(fileButton);
    formLayout->addRow(sqliteButton);


    QDialogButtonBox *controlButtonBox = new QDialogButtonBox;
    controlButtonBox->setOrientation(Qt::Vertical);
    controlButtonBox->addButton(QDialogButtonBox::Save);
    controlButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(controlButtonBox, SIGNAL(accepted()),
            SLOT(accept()));
    connect(controlButtonBox, SIGNAL(rejected()),
            SLOT(reject()));



    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(frame);
    mainLayout->addWidget(controlButtonBox);

    setLayout(mainLayout);

    setWindowTitle(trUtf8("Document Dialog"));


    resize(parent->width() * 9/10, parent->height() * 9/10);
}

void EditDialog::accept()
{
    QString doc       = m_docLineEdit->text();
    QString version   = m_versionLineEdit->text();
    QString org       = m_orgLineEdit->text();
    QString issueNum  = m_issueNumLineEdit->text();
    QDate   issueDate = m_issueDateEdit->date();
    QString note      = m_noteTextEdit->toPlainText();
    QString tags      = m_tagsLineEdit->text();


    QSqlDatabase::database().transaction();

    QSqlQuery orgQuery;
    orgQuery.prepare("SELECT id FROM org WHERE orgRu=:org");
    orgQuery.bindValue(":org", org);
    orgQuery.exec();

    QString org_id;
    int field_org_id = orgQuery.record().indexOf("id");
    while (orgQuery.next()) {
        org_id = orgQuery.value(field_org_id).toString();
    }

    QSqlQuery query;
    query.prepare("UPDATE docs SET "
                  "doc=:doc, version=:version, org_id=:org_id, issueNum=:issueNum, issueDate=:issueDate, note=:note, tags=:tags "
                  "WHERE id=:id");
    query.bindValue(":doc", doc);
    query.bindValue(":version", version);
    query.bindValue(":org_id", org_id);
    query.bindValue(":issueNum", issueNum);
    query.bindValue(":issueDate", issueDate);
    query.bindValue(":note", note);
    query.bindValue(":tags", tags);
    query.bindValue(":id", m_id);
    query.exec();
    if (query.lastError().isValid()) {
        qDebug() << "ERROR" << query.lastError().text();
        QSqlDatabase::database().rollback();
    } else {
        QSqlDatabase::database().commit();
    }


    done(QDialog::Accepted);
}

void EditDialog::reject()
{
    done(QDialog::Rejected);
}

void EditDialog::on_fileButtonClicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    if (fileDialog->exec() == QDialog::Accepted) {
        QString fileName = fileDialog->selectedFiles().at(0);
        if (fileName.isEmpty()) {
            return;
        }

        QFile file(fileName);
        if (file.exists()) {
            if (file.open(QFile::ReadOnly)) {
                QByteArray context = file.readAll();

                QSqlDatabase::database().transaction();
                QSqlQuery query;
                query.prepare("UPDATE docs "
                              "SET context=:context "
                              "WHERE id=:id");
                query.bindValue(":context", context);
                query.bindValue(":id", m_id);
                query.exec();
                if (query.lastError().isValid()) {
                    qDebug() << "ERROR" << query.lastError().text();
                    QSqlDatabase::database().rollback();
                } else {
                    QSqlDatabase::database().commit();
                }

                file.close();
            }
        }
    }
}

void EditDialog::on_sqliteButtonClicked()
{
    QDir dir("/usr/share/vyborg/db/data/aviaDocs/pdf");
    if (!dir.exists()) {
        qDebug() << "Creating new pdf directory";
        dir.mkdir("/usr/share/vyborg/db/aviaDocs/pdf");
    }

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT context FROM docs WHERE id=:id");
    query.bindValue(":id", m_id);
    query.exec();
    while (query.next()) {
        QByteArray context = query.value(0).toByteArray();
        qDebug() << "Size: " << context.size();
        QSqlDatabase::database().commit();

        QFile file("/usr/share/vyborg/db/data/aviaDocs/pdf/" + QString::number(m_id) + ".pdf");
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "ERROR: Unable to open file for writing";
        }
        file.write(context);
        file.close();
    }
}

void EditDialog::on_addOrgButtonClicked()
{
    OrgDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString org = dialog.retValue();
        m_orgLineEdit->setText(org);
    }
}
