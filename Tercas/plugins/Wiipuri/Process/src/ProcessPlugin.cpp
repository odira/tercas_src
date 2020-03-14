#include <QtQml>
#include <QObject>

#include "ProcessPlugin.h"
#include "Process.h"

//static QObject *Process_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
//{
//    Q_UNUSED(engine)
//    Q_UNUSED(scriptEngine)

//    Process *process = new Process();
//    return process;
//}

void ProcessPlugin::registerTypes(const char *uri)
{
    // @uri Wiipuri.Process
    qmlRegisterType<Process>(uri, 1, 0, "Process");
//        qmlRegisterSingletonType<Process>(uri, 1, 0, "Process", Process_singletontype_provider);
}
