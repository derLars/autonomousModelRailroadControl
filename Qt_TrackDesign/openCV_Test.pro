#-------------------------------------------------
#
# Project created by QtCreator 2015-08-02T10:40:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openCV_Test
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += /usr/include/opencv
LIBS += -L/usr/lib -lopencv_core -lopencv_highgui

SOURCES += main.cpp\
        mainwindow.cpp \
    railpiece.cpp \
    rail.cpp

HEADERS  += mainwindow.h \
    railpiece.h \
    rail.h

FORMS    += mainwindow.ui
