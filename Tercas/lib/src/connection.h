#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>

#include <QDebug>

bool openConnection()
{
#ifdef SQLITE

    #ifndef SQLITE_FILE
        #define SQLITE_FILE "resources/aviation.sqlite3"
    #endif

    QFile file_(SQLITE_FILE);
    if (file_.exists()) {
        QSqlDatabase db_ = QSqlDatabase::addDatabase("QSQLITE");
        db_.setDatabaseName(SQLITE_FILE);
        db_.open();
        return true;
    } else {
        QMessageBox::critical(0,
                              QObject::trUtf8("QSQLITE connection error"),
                              QObject::trUtf8("Database file not found"),
                              QMessageBox::Cancel);
        return false;
    }

#elif defined MYSQL

    #ifndef MYSQL_DATABASE
        #define MYSQL_DATABASE "terkas"
    #endif
    #ifndef MYSQL_HOSTNAME
        #define MYSQL_HOSTNAME "localhost"
    #endif
    #ifndef MYSQL_USER
        #define MYSQL_USER "root"
    #endif
    #ifndef MYSQL_PASSWORD
        #define MYSQL_PASSWORD "monrepo"
    #endif

    QSqlDatabase db_ = QSqlDatabase::addDatabase("QMYSQL");
    db_.setHostName(MYSQL_HOSTNAME);
    db_.setUserName(MYSQL_USER);
    db_.setPassword(MYSQL_PASSWORD);
    db_.setDatabaseName(MYSQL_DATABASE);
    if (!db_.open()) {
        QMessageBox::critical(0,
                              QObject::trUtf8("Database connection error"),
                              db_.lastError().text(),
                              QMessageBox::Cancel);
        return false;
    }

    return true;

#elif defined PGSQL

    #ifndef PGSQL_HOSTNAME
        #define PGSQL_HOSTNAME "localhost"
//        #define PGSQL_HOSTNAME "194.1.237.79"
    #endif

    #ifndef PGSQL_USER
        #define PGSQL_USER "postgres"
    #endif

    #ifndef PGSQL_PASSWORD
        #define PGSQL_PASSWORD "monrepo"
    #endif

    #ifndef PGSQL_DATABASE
        #define PGSQL_DATABASE "terkas"
    #endif

    QSqlDatabase db_ = QSqlDatabase::addDatabase("QPSQL");
    db_.setHostName(PGSQL_HOSTNAME);
    db_.setUserName(PGSQL_USER);
    db_.setPassword(PGSQL_PASSWORD);
    db_.setDatabaseName(PGSQL_DATABASE);
    if (!db_.open()) {
//        QMessageBox::critical(0,
//                              QObject::trUtf8("Database connection error"),
//                              db_.lastError().text(),
//                              QMessageBox::Cancel);
        qDebug() << "Database connection error" << db_.lastError().text();
        return false;
    }

    return true;

#endif
}

bool closeConnection()
{
#ifdef SQLITE
    QSqlDatabase::removeDatabase("QSQLITE");
#elif defined MYSQL
    QSqlDatabase::removeDatabase("QMYSQL");
#elif defined PGSQL
    QSqlDatabase::removeDatabase("QPSQL");
#endif

    return true;
}
