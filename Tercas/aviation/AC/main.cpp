#include <QApplication>

#include "declarations.h"
#include <vyborg_connection.h>

#include "maindialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection())
        return -1;

    MainDialog mainDialog;
    mainDialog.showMaximized();

    app.exec();

    if (!closeConnection())
        return -1;

    return 0;
}
