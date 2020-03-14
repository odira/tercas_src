TEMPLATE = lib
QT += qml quick
CONFIG += qt plugin c++11
TARGET = WiipuriProcess
TARGET = $$qtLibraryTarget($$TARGET)

uri = Wiipuri.Process

MOC_DIR = tmp
OBJECTS_DIR = tmp

# static plugin must use this
#CONFIG += static
#QMAKE_MOC_OPTIONS += -Muri=$$uri

include(src/files.pri)

RESOURCES = \
    resources.qrc

qmldir.files = qmldir
qmltypes.files = *.qmltypes
qmlfiles.files = *.qml *.js qml/*.qml js/*.js
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

    target.path = $$installPath
    qmldir.path = $$installPath
    qmltypes.path = $$installPath
    qmlfiles.path = $$installPath

    INSTALLS += target qmldir qmltypes qmlfiles
}

#DISTFILES += \
#    qml/Nothing.qml
