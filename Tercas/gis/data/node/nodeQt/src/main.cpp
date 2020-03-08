#include <QApplication>

#include "../model/NodeTableModel.h"
#include <connection.h>

#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection())
        return -1;

    MainDialog mainDialog;
    mainDialog.setTitle(QObject::tr("База данных NODES"));
    mainDialog.showMaximized();
//    mainDialog.resize(800, 600);
    mainDialog.show();

    app.exec();

    if (!closeConnection())
        return -1;
    else
        return 0;
}
