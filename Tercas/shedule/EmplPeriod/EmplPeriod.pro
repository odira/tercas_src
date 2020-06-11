QT += quick sql widgets qml quickcontrols2
CONFIG += c++17 vyborg

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(src/files.pri)

RESOURCES += qml.qrc


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    qml/main.qml
