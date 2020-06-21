QT += qml quick sql widgets
CONFIG += vyborg
TEMPLATE = app
TARGET = EmplSheduleMonth

unix: DESTDIR = /usr/local/bin/vyborg

MOC_DIR = tmp
OBJECTS_DIR = tmp

include(src/files.pri)

RESOURCES += qml.qrc
