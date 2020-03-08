#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QtSql>
#include <QSqlError>

#include "SafetyModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("monrepo");
    db.setDatabaseName("terkas");
    if (!db.open()) {
        qDebug() << "ERROR: Database not opened: " << db.lastError().text();
        return 0;
    }

    SafetyModel *safetyModel = new SafetyModel;

    QQuickView *view = new QQuickView;
    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("safetyModel", QVariant::fromValue(safetyModel));
    view->setSource(QStringLiteral("qrc:///qml/main.qml"));
    view->show();


    return app.exec();
}
