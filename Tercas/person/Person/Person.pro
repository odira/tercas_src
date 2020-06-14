QT += quick sql qml widgets quickcontrols2
CONFIG += c++17 vyborg

include(src/files.pri)

RESOURCES += qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    src/files.pri
