#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T15:33:27
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vkMusicPlayerQt
TEMPLATE = app


SOURCES += main.cpp\
        vkstartwindow.cpp

HEADERS  += vkstartwindow.h

FORMS    += vkstartwindow.ui

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
