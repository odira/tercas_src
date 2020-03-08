QT += core gui widgets sql positioning
TARGET = nodeQt
TEMPLATE = app
CONFIG += vyborg
linux:DESTDIR = /usr/local/bin/vyborg
macx:DESTDIR = /usr/local/bin/vyborg

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(../model/files.pri)
include(src/files.pri)
