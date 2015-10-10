#-------------------------------------------------
#
# Project created by QtCreator 2015-07-30T14:52:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = HA_1.00
TEMPLATE = app

SOURCES += mainwindow.cpp \
    pWaterTemp.cpp \
    Lib/valueWidget.cpp \
    Lib/valueSetWidget.cpp \
    Lib/HistogramView.cpp

HEADERS  += mainwindow.h \
    pWaterTemp.h \
    css.h \
    Lib/data.h \
    Lib/valueSetWidget.h \
    Lib/valueWidget.h \
    Lib/HistogramView.h \
    workerhttp.h

FORMS    += mainwindow.ui \
    pWaterTemp.ui

CONFIG += mobility \

QMAKE_CXXFLAGS += -std=c++11

MOBILITY =

DISTFILES +=

RESOURCES += \
    resources.qrc

