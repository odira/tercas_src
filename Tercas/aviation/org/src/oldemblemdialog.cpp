#include <QtWidgets>
#include <QtSql>

#include "emblemdialog.h"


EmblemDialog::EmblemDialog(const int id, QWidget *parent)
    : QDialog(parent), m_id(id)
{
}



//                QFile file(fileList.at(0));
//                if (file.exists()) {
//                    if (file.open(QFile::ReadOnly)) {
//                        QByteArray emblem = file.readAll();

//                        QSqlDatabase::database().transaction();
//                        QSqlQuery query;
//                        query.prepare("UPDATE org "
//                                      "SET emblem=:emblem "
//                                      "WHERE id=:id");
//                        query.bindValue(":emblem", emblem);
//                        query.bindValue(":id", m_id);
//                        query.exec();
//                        if (query.lastError().isValid()) {
//                            qDebug() << "ERROR" << query.lastError().text();
//                            QSqlDatabase::database().rollback();
//                        } else {
//                            QSqlDatabase::database().commit();
//                        }

//                        file.close();
//                    }
