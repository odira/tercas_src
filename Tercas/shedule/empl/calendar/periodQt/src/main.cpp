#include <QApplication>

#define PGSQL
#define PGSQL_DATABASE "terkas"
#include <connection.h>

#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection())
        return -1;

    MainDialog mainDialog;
    mainDialog.setTitle(QObject::trUtf8("Рабочий календарь (ИНТЕРВАЛЬНЫЙ)"));
    mainDialog.setMinimumWidth(1400);
    mainDialog.setMinimumHeight(800);
    mainDialog.show(); // mainDialog.showMaximized();

    app.exec();

    if (!closeConnection())
        return -1;
    else
        return 0;
}
