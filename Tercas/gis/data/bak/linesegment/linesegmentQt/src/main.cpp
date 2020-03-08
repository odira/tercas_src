#include <QApplication>

// The order of the include for following files is IMPORTANT
#include "../model/LineSegmentModel.h"
#include <connection.h>

#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!openConnection()) {
        return -1;
    }

    MainDialog mainDialog;
    mainDialog.setTitle("Line Segment");
    mainDialog.showMaximized();

    app.exec();

    if (!closeConnection()) {
        return -1;
    }

    return 0;
}
