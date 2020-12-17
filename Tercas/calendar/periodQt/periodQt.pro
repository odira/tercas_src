QT += core gui widgets sql
CONFIG += vyborg release sdk_no_version_check
TEMPLATE = app
TARGET = periodQt

macx {
    DESTDIR = /usr/local/bin/vyborg
}
linux {
    DESTDIR = /home/debian/bin
}

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)
