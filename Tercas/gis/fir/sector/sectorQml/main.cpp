#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

#include "../model/declarations.h"
#include <connection.h>

#include "../model/GisSectorModel.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    GisSectorModel *sectorModel = new GisSectorModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sectorModel", QVariant::fromValue(sectorModel));
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    app.exec();

    if (!closeConnection())
        return -1;

    return 0;
}
