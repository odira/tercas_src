#include <QApplication>

#include "declarations.h"
#include <vyborg/connection.h>

#include "maindialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection())
        return 1;


    MainDialog dialog;
//    dialog.showMaximized();
    dialog.resize(1000, 500);
    dialog.show();

    app.exec();

    if (!closeConnection())
        return -1;

    return 0;
}
