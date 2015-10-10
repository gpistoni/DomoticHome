#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T15:32:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = Home
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cwidgettair.cpp \
    cwidgetvl.cpp \
    ../libraries/HistogramView.cpp \
    ../libraries/valueSetWidget.cpp \
    ../libraries/valueWidget.cpp \
    ../libraries/data.cpp

HEADERS  += mainwindow.h \
    cwidgettair.h \
    cwidgetvl.h \
    ../libraries/data.h \
    ../libraries/HistogramView.h \
    ../libraries/valueSetWidget.h \
    ../libraries/valueWidget.h \
    workerhttp.h \
    css.h

FORMS    += mainwindow.ui \
    widgetvl.ui


QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    icons.qrc
