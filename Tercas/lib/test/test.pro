QT       += core gui widgets sql

TARGET = wiipuriTest
TEMPLATE = app

INCLUDEPATH += ../lib/src


SOURCES += main.cpp \
    dialog.cpp \
    ../src/navigationbuttonbox.cpp \
    ../src/yearmonth.cpp \
    ../src/yearmonthwidget.cpp \
    ../src/maindialogcontrolbuttonbox.cpp \
    ../src/mappercontrolbuttonbox.cpp \
    ../src/mapperdialog.cpp

HEADERS  += \
    dialog.h \
    ../src/navigationbuttonbox.h \
    ../src/yearmonth.h \
    ../src/yearmonthwidget.h \
    ../src/maindialogcontrolbuttonbox.h \
    ../src/mappercontrolbuttonbox.h \
    ../src/mapperdialog.h
