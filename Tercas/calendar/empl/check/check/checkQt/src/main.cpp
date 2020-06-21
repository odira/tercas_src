#include <QApplication>

// The order of the include for following files is IMPORTANT
#include "../model/EmplSectorCheckModel.h"
#include <connection.h>

#include "maindialog.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection()) {
        return -1;
    }

    MainDialog mainDialog;
    mainDialog.setTitle("Прохождение Проверок на Секторе");
    mainDialog.resize(1024, 1024);
    mainDialog.show();

    app.exec();

    if (!closeConnection()) {
        return -1;
    }

    return 0;
}
