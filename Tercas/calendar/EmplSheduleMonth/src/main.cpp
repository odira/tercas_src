#include <QCoreApplication>
#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Здесь важен порядок следования файлов - connection.h за хедером модели!
#include "src/EmplSheduleMonthModel.h"
#include <connection.h>

#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QString lockFileName = QString(QCoreApplication::applicationName() + ".lock");
    QLockFile lockFile(QDir::temp().absoluteFilePath(lockFileName));
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

    EmplSheduleMonthModel *emplSheduleMonthModel = new EmplSheduleMonthModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("emplSheduleMonthModel", QVariant::fromValue(emplSheduleMonthModel));
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    if (!closeConnection()) {
        return -1;
    }

    return app.exec();
}
