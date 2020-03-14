TEMPLATE = app
QT += quick sql widgets
CONFIG += c++17 vyborg
DESTDIR = /usr/local/bin/vyborg
TARGET = TotalMonth
RESOURCES += qml.qrc

MOC_DIR = tmp
OBJECTS_DIR = tmp

include(src/files.pri)
include(model/files.pri)
