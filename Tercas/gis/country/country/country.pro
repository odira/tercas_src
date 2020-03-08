TEMPLATE = app
TARGET   = vyborg_country


QT += sql widgets gui core

OBJECTS_DIR = tmp
MOC_DIR = tmp

# Input

#DISTFILES += \
#    src/files.pri

include(src/files.pri)

#DEPENDPATH  += .

INCLUDEPATH += /usr/local/include/vyborg
LIBS += -L/usr/local/lib/vyborg -lvyborg
