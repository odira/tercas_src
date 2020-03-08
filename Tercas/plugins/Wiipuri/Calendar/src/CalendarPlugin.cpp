#include <QtQml>
#include <QObject>

#include "CalendarPlugin.h"
#include "TercasDate.h"

static QObject *TercasDate_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    TercasDate *tercasDate = new TercasDate();
    return tercasDate;
}

void CalendarPlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<TercasDate>(uri, 1, 0, "TercasDate", TercasDate_singletontype_provider);
}
