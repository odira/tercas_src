#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "EmplSheduleYearModel.h"
#include <connection.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection()) {
        return -1;
    }


    EmplSheduleYearModel *emplSheduleYearModel = new EmplSheduleYearModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("emplSheduleYearModel", QVariant::fromValue(emplSheduleYearModel));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
