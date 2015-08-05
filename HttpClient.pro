#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T15:56:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = HttpClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util/utility.cpp

HEADERS  += mainwindow.h \
    util/utility.h

FORMS    += mainwindow.ui
