#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <QtSql>
//#include <QSqlError>

//#include "../model/declarations.h"
#include <connection.h>

#include "../model/EmplSectorCheckModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!openConnection())
        return -1;

    EmplSectorCheckModel *emplSectorCheckModel = new EmplSectorCheckModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("emplSectorCheckModel", QVariant::fromValue(emplSectorCheckModel));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();

    if (!closeConnection())
        return -1;
}
