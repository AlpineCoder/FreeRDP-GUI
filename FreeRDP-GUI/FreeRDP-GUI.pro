#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T00:15:06
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FreeRDP-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xfreerdp.cpp

HEADERS  += mainwindow.h \
    xfreerdp.h

FORMS    += mainwindow.ui
