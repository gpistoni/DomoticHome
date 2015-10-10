#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T15:32:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Home
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgetvl.cpp

HEADERS  += mainwindow.h \
    widgetvl.h

FORMS    += mainwindow.ui \
    widgetvl.ui


QMAKE_CXXFLAGS += -std=c++11
