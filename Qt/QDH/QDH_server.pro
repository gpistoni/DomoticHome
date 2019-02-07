#-------------------------------------------------
#
# Project created by QtCreator 2018-11-24T13:15:06
#
#-------------------------------------------------
F
QT += core
QT -= gui
QT += websockets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = /root/dh/dh_server

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    server.cpp \
    ../QLibrary/HttpClient.cpp \
    ../QLibrary/HttpParser.cpp \
    ../QLibrary/HttpServer.cpp \
    ../QLibrary/DataTable.cpp \
    ../QLibrary/DataVars.cpp \
    ../QLibrary/InfoBarVar.cpp \
    ../QLibrary/InfoTempSetpoint.cpp \
    ../QWidget/LogMessage.cpp \
    ../QWidget/ButtonVarOnOffAuto.cpp \
    ../QWidget/ButtonVar.cpp \
    main_server.cpp

HEADERS += \
    server.h \
    ../QLibrary/HttpClient.h \
    ../QLibrary/HttpParser.h \
    ../QLibrary/HttpServer.h \
    ../QLibrary/DataTable.h \
    ../QLibrary/DataVars.h \
    ../QLibrary/InfoBarVar.h \
    ../QLibrary/InfoTempSetpoint.h \
    ../QWidget/ButtonVarOnOffAuto.h \
    ../QWidget/ButtonVar.h \
    ../QWidget/LogMessage.h

FORMS +=
