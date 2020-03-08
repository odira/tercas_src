QT += quick
CONFIG += c++11
TARGET = dashboard
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp \
    src/WatcherModel.cpp \
    src/RestrictionModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

DISTFILES +=

HEADERS += \
    src/WatcherModel.h \
    src/RestrictionModel.h
