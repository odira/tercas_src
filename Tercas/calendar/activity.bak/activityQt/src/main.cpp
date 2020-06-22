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
    mainDialog.setTitle(QObject::tr("Вид деятельности работника/производства"));
    mainDialog.showMaximized();

    app.exec();

    if (!closeConnection())
        return -1;

    return 0;
}
