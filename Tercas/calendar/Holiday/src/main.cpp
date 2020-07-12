#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//#include <QQuickStyle>

#include "HolidayModel.h"
#include <connection.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    QQuickStyle::setStyle("Imagine");

    if (!openConnection())
        return -1;

    HolidayModel *holidayModel = new HolidayModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("holidayModel", QVariant::fromValue(holidayModel));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    if (!closeConnection())
        return -1;
    else
        return app.exec();
}
