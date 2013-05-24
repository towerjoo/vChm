#-------------------------------------------------
#
# Project created by QtCreator 2013-05-24T15:21:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vChm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    userdatamanager.cpp \
    settingsmanager.cpp

HEADERS  += mainwindow.h \
    commands.h \
    userdatamanager.h \
    settingsmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
