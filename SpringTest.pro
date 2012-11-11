#-------------------------------------------------
#
# Project created by QtCreator 2012-11-10T19:57:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpringTest
TEMPLATE = app

QMAKE_CXXFLAGS+=--std=gnu++11

SOURCES += main.cpp\
        mainwindow.cpp \
    spring.cpp \
    spring_solving.cpp

HEADERS  += mainwindow.h \
    spring.h \
    basics.h \
    spring_solving.h

FORMS    += mainwindow.ui
