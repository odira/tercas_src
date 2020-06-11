#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "EmplPeriodModel.h"
#include <connection.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    EmplPeriodModel * periodModel = new EmplPeriodModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("periodModel", QVariant::fromValue(periodModel));
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    if (!closeConnection())
        return -1;
    else
        return app.exec();
}
