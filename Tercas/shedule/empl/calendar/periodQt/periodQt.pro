QT += core gui widgets sql
TEMPLATE = app
CONFIG += vyborg
TARGET = emplcalendarperiodQt

macx {
    DESTDIR = /usr/local/bin/vyborg
}
linux {
    DESTDIR = /home/debian/bin
}

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)
#include(../model/files.pri)
