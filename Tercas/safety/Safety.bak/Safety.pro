QT += qml network quick positioning location sql
TARGET = Safety
TEMPLATE = app
linux:DESTDIR = /home/debian/bin
macx:DESTDIR = /usr/local/bin/vyborg/safety

MOC_DIR = tmp
OBJECTS_DIR = tmp

RESOURCES += \
    resources.qrc

include(src/files.pri)
