QT += core gui widgets sql
TARGET = sectorQt
TEMPLATE = app
CONFIG += vyborg
macx | linux : DESTDIR = /usr/local/bin/vyborg
DESTDIR += ~/Desktop

include(src/files.pri)
include(../model/files.pri)

OBJECTS_DIR = tmp
MOC_DIR = tmp
