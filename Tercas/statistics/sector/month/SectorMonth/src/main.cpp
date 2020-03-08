#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "model/SectorMonthModel.h"
#include <connection.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    qmlRegisterType<SectorMonthModel>("Wiipuri.Models", 1, 0, "SectorMonthModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    app.exec();

    if (!closeConnection())
        return -1;
    else
        return 0;
}
