#include <QSqlError>

#include "Database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(HOSTNAME);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);
    db.setDatabaseName(DATABASE);
    if (!db.open()) {
        QSqlError error = db.lastError().text();
    }
}

Database::~Database()
{

}
