TEMPLATE = app
QT += quick sql widgets
CONFIG += c++17 vyborg
DESTDIR = /usr/local/bin/vyborg
TARGET = SectorYear
RESOURCES += qml.qrc

include(src/files.pri)
include(model/files.pri)
