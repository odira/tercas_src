#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "model/SectorDateModel.h"
#include <connection.h>

//#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    SectorDateModel *sectorDateModel = new SectorDateModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sectorDateModel", QVariant::fromValue(sectorDateModel));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    app.exec();

    if (!closeConnection())
        return -1;
    else
        return 0;
}
