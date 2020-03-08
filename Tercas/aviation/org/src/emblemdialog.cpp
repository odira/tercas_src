#include <QtWidgets>
#include <QtSql>

#include "emblemdialog.h"
#include "ui_emblemdialog.h"


EmblemDialog::EmblemDialog(const int &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmblemDialog)
{
    m_id = id;
    ui->setupUi(this);

    QPushButton *addButton = new QPushButton(trUtf8("Изменить"));
    connect(addButton, SIGNAL(clicked()),
            SLOT(on_addButtonClicked()));
    ui->buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);

//    QLabel *label = new QLabel;
//    label->setEnabled(false);
//    label->setAlignment(Qt::AlignCenter);
//    label->setFrameShape(QFrame::Box);
//    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    label->setBackgroundRole(QPalette::Base);
//    label->setAutoFillBackground(true);
//    label->setMinimumSize(132, 132);


    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT emblem FROM org WHERE id=:id");
    query.bindValue(":id", m_id);
    query.exec();
    while (query.next()) {
        QByteArray emblem = query.value(0).toByteArray();
        QSqlDatabase::database().commit();

        QPixmap pixmap;
        pixmap.loadFromData(emblem);
        pixmap = pixmap.scaled(132, 132,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
        ui->emblemLabel->setPixmap(pixmap);
    }
}

EmblemDialog::~EmblemDialog()
{
    delete ui;
}

void EmblemDialog::on_addButtonClicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(trUtf8("Images (*.png *.jpg *.gif)"));
    fileDialog.setDirectory(QDir::home());
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec()) {
        QStringList fileNames;
        fileNames = fileDialog.selectedFiles();

        QByteArray emblem;
        QFile file(fileNames.at(0));
        if (file.exists()) {
            file.open(QFile::ReadOnly);
            emblem = file.readAll();
            file.close();

            QPixmap pixmap;
            pixmap.loadFromData(emblem);
            pixmap = pixmap.scaled(132, 132,
                                   Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);
            ui->emblemLabel->setPixmap(pixmap);
        }

        if (emblem.size() > 0) {
            QSqlDatabase::database().transaction();
            QSqlQuery query;
            query.prepare("UPDATE org SET emblem=:emblem WHERE id=:id");
            query.bindValue(":emblem", emblem);
            query.bindValue(":id", m_id);
            query.exec();
            if (query.lastError().isValid()) {
                qDebug() << "ERROR: " << query.lastError().text();
                QSqlDatabase::database().rollback();
            } else {
                qDebug() << "SAVE emblem";
                QSqlDatabase::database().commit();
            }
        }
    }
}
