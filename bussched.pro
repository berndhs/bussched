TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11
CONFIG += console
CONFIG += debug

SOURCES += \
    src/main.cpp \
    src/source.cpp \
    src/buspositions.cpp \
    src/businfo.cpp \
    src/makesvg.cpp \
    src/util.cpp

HEADERS += \
    src/source.h \
    src/buspositions.h \
    src/businfo.h \
    src/makesvg.h \
    src/util.h

RESOURCES += qml.qrc

OBJECTS_DIR = obj

MOC_DIR = moc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    gpl2.txt
