#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T19:29:31
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vkDownloadMusic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    musicview.cpp \
    json.cpp

HEADERS  += mainwindow.h \
    musicview.h \
    json.h

FORMS    += mainwindow.ui \
    musicview.ui
