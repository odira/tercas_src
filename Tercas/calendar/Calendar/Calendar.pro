QT += qml quick widgets quickcontrols2
TEMPLATE = app
CONFIG += c++17
TARGET = Calendar
macx:DESTDIR = /usr/local/bin/vyborg

include(src/files.pri)

RESOURCES += qml.qrc

OBJECTS_DIR = tmp
MOC_DIR = tmp

#android: MULTI = 3
#else: unix: MULTI = 1

#DISTFILES += \
#    src/files.pri
