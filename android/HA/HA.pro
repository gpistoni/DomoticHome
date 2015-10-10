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
    pWork.cpp \
    Lib/valueWidget.cpp \
    Lib/valueSetWidget.cpp \
    Lib/HistogramView.cpp \
    pag1.cpp \
    pag2.cpp \
    pag3.cpp

HEADERS  += mainwindow.h \
    pWork.h \
    css.h \
    Lib/data.h \
    Lib/valueSetWidget.h \
    Lib/valueWidget.h \
    Lib/HistogramView.h \
    workerhttp.h \
    pag1.h \
    pag2.h \
    pag3.h

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

