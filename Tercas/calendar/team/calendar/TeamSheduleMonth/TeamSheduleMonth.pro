QT += qml quick sql widgets
CONFIG += vyborg
DESTDIR = /usr/local/bin/vyborg
TEMPLATE = app
TARGET = TeamSheduleMonth

MOC_DIR = tmp
OBJECTS_DIR = tmp

include(src/files.pri)

RESOURCES += qml.qrc
