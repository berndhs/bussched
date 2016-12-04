TEMPLATE = app

QT += qml widgets network gui

contains(QMAKESPEC,"x86") {
  QMAKE_CC = /usr/bin/gcc
  QMAKE_CXX = /usr/bin/g++
}

CONFIG += c++11
CONFIG += console
CONFIG += debug

message ("qmakespec:")
message ($$QMAKESPEC)
message ("qt vesion:")
message ($$QT_VERSION)
message ("android_ndk_root:")
message ($$ANDROID_NDK_ROOT)
message ("compilers " $$QMAKE_CC " and " $$QMAKE_CXX)

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    gpl2.txt


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
