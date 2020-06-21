QT += quick qml core sql quickcontrols2 widgets
CONFIG += vyborg c++17
TEMPLATE = app
TARGET = Holiday
DESTDIR = /usr/local/bin/vyborg

MOC_DIR = tmp
OBJECTS_DIR = tmp

include(src/files.pri)

RESOURCES += qml.qrc
