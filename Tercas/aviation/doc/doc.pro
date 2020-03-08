TARGET = vyborg_doc
TEMPLATE = app
QT       += core gui widgets sql

include(src/files.pri)

MOC_DIR = tmp
OBJECTS_DIR = tmp

INCLUDEPATH += /usr/include/vyborg
LIBS += -L/usr/lib/vyborg -lvyborg

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    src/files.pri


