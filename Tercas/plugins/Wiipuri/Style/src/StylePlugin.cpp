#include <QtQml>

#include "StylePlugin.h"

void StylePlugin::registerTypes(const char *uri)
{
    // @uri Wiipuri.Style
    qmlRegisterType<StylePlugin>(uri, 1, 0, "StylePlugin");
}

