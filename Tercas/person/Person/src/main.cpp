#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "PersonModel.h"
//#include <connection.h>

#include "Database.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Database db;

//    if (!openConnection())
//        return -1;

    PersonModel * personModel = new PersonModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("personModel", QVariant::fromValue(personModel));
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

//    if (!closeConnection())
//        return -1;
//    else
        return app.exec();
}
