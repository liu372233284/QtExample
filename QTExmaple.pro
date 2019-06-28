#-------------------------------------------------
#
# Project created by QtCreator 2019-05-13T13:50:35
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTExmaple
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iconsizespinbox.cpp \
    cardlayout.cpp \
    flowlayout.cpp \
    qborderlayout.cpp \
    qcardlayoutwidget.cpp \
    filesystemwatcher.cpp \
    paintfoutwidget.cpp

HEADERS  += mainwindow.h \
    iconsizespinbox.h \
    toolbox.h \
    traymenu.h \
    cardlayout.h \
    flowlayout.h \
    qborderlayout.h \
    qcardlayoutwidget.h \
    filesystemwatcher.h \
    paintfoutwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
