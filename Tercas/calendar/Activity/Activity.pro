QT += core gui widgets sql quickwidgets
TEMPLATE = app
CONFIG += vyborg
TARGET = activity
macx | linux : {
    DESTDIR = /usr/local/bin/vyborg
}

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)
include(../model/files.pri)

RESOURCES += \
    resources.qrc
