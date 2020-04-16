#include <QCoreApplication>
#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Здесь важен порядок следования файлов - connection.h за хедером модели!
#include "TeamSheduleMonthModel.h"
#include <connection.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QLockFile lockFile(QDir::temp().absoluteFilePath("EmplSheduleMonth.lock"));

    /* Пытаемся закрыть Lock File, если попытка безуспешна в течение 100 миллисекунд,
     * значит уже существует Lock File созданный другим процессом.
     * Следовательно, выбрасываем предупреждение и закрываем программу
     * */
    if (!lockFile.tryLock(100)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Приложение уже запущено.\n"
                       "Разрешено запускать только один экземпляр приложения.");
        msgBox.exec();
        return 1;
    }

    if (!openConnection()) {
        return -1;
    }

    /*
     * Defining models
     * */
//    EmplSheduleMonthModel *emplSheduleMonthModel = new EmplSheduleMonthModel;
    TeamSheduleMonthModel *model = new TeamSheduleMonthModel;

    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("emplSheduleMonthModel", QVariant::fromValue(emplSheduleMonthModel));
    engine.rootContext()->setContextProperty("teamSheduleMonthModel", QVariant::fromValue(model));
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    if (!closeConnection()) {
        return -1;
    }

    return app.exec();
}
