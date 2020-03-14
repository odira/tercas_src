TEMPLATE = lib
QT += qml quick
CONFIG += qt plugin c++11
TARGET = WiipuriCalendar
TARGET = $$qtLibraryTarget($$TARGET)

uri = Wiipuri.Calendar

# static plugin must use this
#CONFIG += static
#QMAKE_MOC_OPTIONS += -Muri=$$uri

MOC_DIR = tmp
OBJECTS_DIR = tmp

include(src/files.pri)

RESOURCES = \
    resources.qrc

# Input

#DISTFILES = qmldir \
#    qml/qmldir \
#    qml/DatePicker.qml \
#    qml/CalendarPlugin.qml \
#    qml/DirectionButton.qml \
#    js/funcCalendar.js
#    src/files.pri


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
