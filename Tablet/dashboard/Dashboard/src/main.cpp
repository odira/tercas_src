#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "RestrictionModel.h"
#include "WatcherModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<RestrictionModel>("RestrictionModel", 1, 0, "RestrictionModel");
    qmlRegisterType<WatcherModel>("WatcherModel", 1, 0, "WatcherModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/dashboard.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
