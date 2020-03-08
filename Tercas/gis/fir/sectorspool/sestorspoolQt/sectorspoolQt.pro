QT += core gui widgets sql
# Uncomment to include QtCharts module
# Qt += charts

TEMPLATE = app
TARGET = sectorspoolQt  # Rename for correct application name
CONFIG += vyborg

macx:DESTDIR = /usr/local/bin  # Rename for correct destination
linux:DESTDIR = /home/debian/bin  # Rename for correct destination

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)
include(../model/files.pri)

