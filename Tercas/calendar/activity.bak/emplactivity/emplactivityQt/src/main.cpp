#include <QApplication>

#include <connection.h>

#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection())
        return -1;

    MainDialog mainDialog;
    mainDialog.setTitle("Вид деятельности работника");
    mainDialog.showMaximized();

    app.exec();

    if (!closeConnection())
        return -1;

    return 0;
}
