QT += core gui widgets sql

TEMPLATE = app
TARGET = segmentQt
CONFIG += vyborg

macx:DESTDIR = /usr/local/bin
linux:DESTDIR = /home/debian/bin

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)
include(../model/files.pri)

