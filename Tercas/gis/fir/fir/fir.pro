QT += core gui widgets sql
TARGET = firQt
TEMPLATE = app
CONFIG += vyborg
DESTDIR = /usr/local/bin/vyborg

include(src/files.pri)

OBJECTS_DIR = tmp
MOC_DIR = tmp

DISTFILES += \
    src/files.pri
