#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TercasDate.h"
#include "model/HourSectorModel.h"
#include <connection.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    QDate date = QDate(2020, 1, 1);
    TercasDate terkasDate;
    terkasDate.setDate(date);
    HourSectorModel *hourSectorModel = new HourSectorModel(date);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("hourSectorModel", QVariant::fromValue(hourSectorModel));
    engine.rootContext()->setContextProperty("terkasDate", QVariant::fromValue(&terkasDate));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    app.exec();

    if (!closeConnection())
        return -1;
    else
        return 0;
}
