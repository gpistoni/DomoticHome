HEADERS       = \
    ../QLibrary/DataReader.h \
    ../QLibrary/HttpParser.h \
    ../QLibrary/HttpClient.h \
    ../QLibrary/HttpParser.h

SOURCES       = \
    main-ctrl.cpp \
    ../QLibrary/HttpClient.cpp \
    ../QLibrary/HttpParser.cpp \
    ../QLibrary/HttpServer.cpp
	
QT  += network websockets

CONFIG += console
