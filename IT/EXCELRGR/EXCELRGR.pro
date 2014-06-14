#-------------------------------------------------
#
# Project created by QtCreator 2014-05-12T19:06:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EXCELRGR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    welcomeform.cpp \
    funchelp.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    welcomeform.h \
    funchelp.h \
    about.h

FORMS    += mainwindow.ui \
    welcomeform.ui \
    funchelp.ui \
    about.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    funcs.txt \
    abs.txt \
    asin.txt \
    atan.txt \
    cos.txt \
    exp.txt \
    floor.txt \
    log.txt \
    log10.txt \
    max.txt \
    min.txt \
    pow.txt \
    round.txt \
    sin.txt \
    sinh.txt \
    sqrt.txt \
    sum.txt \
    tan.txt \
    tanh.txt
