#-------------------------------------------------
#
# Project created by QtCreator 2015-07-30T14:52:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = HA_1.00
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    pAirTemp.cpp \
    pWaterTemp.cpp \
    pMenu.cpp \
    pWork.cpp \
    Lib/valueWidget.cpp \
    Lib/valueSetWidget.cpp \
    Lib/HistogramView.cpp

HEADERS  += mainwindow.h \
    pAirTemp.h \
    pWaterTemp.h \
    pMenu.h \
    pWork.h \
    css.h \
    workerHttp.h \
    Lib/data.h \
    Lib/valueSetWidget.h \
    Lib/valueWidget.h \
    Lib/HistogramView.h

FORMS    += mainwindow.ui \
    pWaterTemp.ui \
    pAirTemp.ui \
    pMenu.ui \
    pWork.ui \
    _test_frame.ui

CONFIG += mobility \

QMAKE_CXXFLAGS += -std=c++11

MOBILITY =

DISTFILES +=

RESOURCES += \
    resources.qrc

