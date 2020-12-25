QT += core gui widgets sql
TARGET = sectorQt
TEMPLATE = app
CONFIG += vyborg sdk_no_version_check

macx | linux : DESTDIR = /usr/local/bin/vyborg
DESTDIR += ~/Desktop

include(src/files.pri)
include(../model/files.pri)

OBJECTS_DIR = tmp
MOC_DIR = tmp
