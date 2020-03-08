TEMPLATE = lib
TARGET = WiipuriStyle
TARGET = $$qtLibraryTarget($$TARGET)
QT += qml quick
CONFIG += plugin c++11 qt
uri = Wiipuri.Style

include(src/files.pri)

#DISTFILES = qmldir \
#    src/files.pri

#!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
#    copy_qmldir.target = $$OUT_PWD/qmldir
#    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
#    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
#    QMAKE_EXTRA_TARGETS += copy_qmldir
#    PRE_TARGETDEPS += $$copy_qmldir.target
#}

qmldir.files = qmldir
qmlfiles.files = *.qml *.js qml/*.qml js/*.js
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    qmlfiles.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir qmlfiles
}

RESOURCES += \
    resources.qrc
