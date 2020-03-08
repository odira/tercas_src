QT       += core gui widgets sql

OBJECTS_DIR = tmp
MOC_DIR = tmp

INCLUDEPATH += /usr/include/vyborg
LIBS += -L/usr/lib/vyborg -lvyborg

TARGET = aviation_AC
TEMPLATE = app


SOURCES += main.cpp\
    maindialog.cpp \
    mapperdialog.cpp

HEADERS  += \
    maindialog.h \
    declarations.h \
    mapperdialog.h
