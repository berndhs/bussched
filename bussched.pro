TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11
CONFIG += console
CONFIG += debug

SOURCES += \
    src/main.cpp \
    src/source.cpp

HEADERS += \
    src/source.h

RESOURCES += qml.qrc

OBJECTS_DIR = obj

MOC_DIR = moc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
