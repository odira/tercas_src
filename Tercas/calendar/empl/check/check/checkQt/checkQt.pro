QT += core gui widgets sql
TEMPLATE = app
CONFIG += vyborg
TARGET = emplsectorcheckQt
macx | linux : DESTDIR = /usr/local/bin/

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)
include(../model/files.pri)


