#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "model/TotalMonthModel.h"
#include <connection.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    qmlRegisterType<TotalMonthModel>("Wiipuri.Models", 1, 0, "TotalMonthModel");

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
