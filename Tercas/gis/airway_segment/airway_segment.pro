QT       += core gui sql widgets

TARGET = airway_segment
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    relationaltablemodel.cpp \
    mapperdialog.cpp

HEADERS  += widget.h \
    relationaltablemodel.h \
    mapperdialog.h \
    declarations.h
