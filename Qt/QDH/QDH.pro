#-------------------------------------------------
#
# Project created by QtCreator 2018-11-24T13:15:06
#
#-------------------------------------------------

QT += core gui
QT += websockets
QT += network
QT += sql
QT += widgets

TARGET = ../../../QDH

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
    dbmanager.cpp \
        mainwindow.cpp \
    server.cpp \
    ../QLibrary/HttpClient.cpp \
    ../QLibrary/HttpParser.cpp \
    ../QLibrary/HttpServer.cpp \
    ../QLibrary/DataTable.cpp \
    ../QLibrary/DataVars.cpp \
    main.cpp \
    ../QWidget/ButtonVarForced.cpp \
    ../QWidget/LogMessage.cpp \
    ../QWidget/InfoTempSetpoint.cpp \
    ../QWidget/InfoBarVar.cpp \
    ../QWidget/ButtonVar.cpp \
    dbevents.cpp \
    ../QLibrary/HttpRequest.cpp

HEADERS += \
    dbmanager.h \
        mainwindow.h \
    server.h \
    ../QLibrary/HttpClient.h \
    ../QLibrary/HttpParser.h \
    ../QLibrary/HttpServer.h \
    ../QLibrary/DataTable.h \
    ../QLibrary/DataVars.h \
    ../QWidget/ButtonVarForced.h \
    ../QWidget/LogMessage.h \
    ../QWidget/InfoTempSetpoint.h \
    ../QWidget/InfoBarVar.h \
    ../QWidget/ButtonVar.h \
    dbevents.h \
    ../QLibrary/HttpRequest.h

FORMS += \
        mainwindow.ui
