QT -= gui
QT += widgets sql core
#QT += core5compat
CONFIG += sdk_no_version_check install
TARGET = vyborg
TEMPLATE = lib
VERSION = 1.15
DEFINES += LIBVYBORG_LIBRARY

OBJECTS_DIR = tmp
MOC_DIR = tmp

include(files.pri)

ios : DIR_PREFIX = /usr/local
macx | linux : DIR_PREFIX = /usr/local/
#macx:DIR_PREFIX=/usr/local/

HEADERS_INSTALL_DIR = $$DIR_PREFIX/include/$$TARGET
LIBS_INSTALL_DIR = $$DIR_PREFIX/lib/$$TARGET

macx | linux | unix {
    headers.extra = mkdir -p $$HEADERS_INSTALL_DIR
    headers.files = $$HEADERS
    headers.path = $$HEADERS_INSTALL_DIR
    INSTALLS += headers

    features.extra = @echo Installing $${TARGET}.prf ... into $${QMAKESPEC}/../features/mac9
    features.files = $${TARGET}.prf
    features.path = $${QMAKESPEC}/../features/mac
    INSTALLS += features

    endup.extra = make install
#    endup.path = $$PWD
    INSTALLS += endup
}

DESTDIR = $$LIBS_INSTALL_DIR

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    vyborg.prf
