QT += core qml quick widgets
CONFIG += c++11
TEMPLATE = app
DESTDIR = /usr/local/bin/vyborg
TARGET = Dashboard

RESOURCES += qml.qrc \
    images.qrc

include(src/files.pri)

