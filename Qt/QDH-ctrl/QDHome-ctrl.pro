HEADERS       = \
    DataReader.h \
    ../QLibrary/QHttpClient.h \
    ../QLibrary/QHttpServer.h \
    ../QLibrary/CHttpParser.h

SOURCES       = \
    ../QLibrary/QHttpClient.cpp \
    ../QLibrary/QHttpServer.cpp \
    ../QLibrary/CHttpParser.cpp
	
QT  += network websockets

CONFIG += console
