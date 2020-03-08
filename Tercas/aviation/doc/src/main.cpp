#include <QApplication>

#include "dialog.h"
#include "declarations.h"
#include <vyborg_connection.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection()) {
        return -1;
    }

    Dialog dialog;
    dialog.setWindowTitle(QObject::trUtf8("Aviation Documents Database"));
    dialog.showMaximized();

    app.exec();

    if (!closeConnection()) {
        return -2;
    }

    return 0;
}
