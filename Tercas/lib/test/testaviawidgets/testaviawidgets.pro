#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T19:20:41
#
#-------------------------------------------------

QT       += core gui widgets sql

TARGET = testaviawidgets
TEMPLATE = app

SOURCES += main.cpp \
    dialog.cpp

HEADERS  += \
    dialog.h

DEPENDPATH += ../libaviawidgets
INCLUDEPATH += /usr/local/include/aviawidgets
LIBS += -L/usr/local/lib/aviawidgets -laviawidgets
