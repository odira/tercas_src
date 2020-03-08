QT       += core gui widgets sql

TARGET = aviation_ACFTmanufacturer
TEMPLATE = app

OBJECTS_DIR = tmp
MOC_DIR = tmp

INCLUDEPATH += /usr/include/vyborg
LIBS += -L/usr/lib/vyborg -lvyborg


SOURCES += main.cpp\
    maindialog.cpp \
    mapperdialog.cpp

HEADERS  += \
    maindialog.h \
    mapperdialog.h \
    declarations.h
