#include <QApplication>

#include "../../model/GisSectorModel.h"
#include <connection.h>

#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection()) {
        return -1;
    }

    MainDialog mainDialog;
    mainDialog.setTitle(QObject::tr("Перечень секторов РДЦ"));
    mainDialog.showMaximized();

    app.exec();

    if (!closeConnection())
        return -1;
    else
        return 0;
}
