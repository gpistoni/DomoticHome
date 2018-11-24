HEADERS       = client.h \
    mainwindow.h \
    server.h \
    SQlabel.h \
    SQHttpClient.h

SOURCES       = client.cpp \
                main.cpp \
    mainwindow.cpp \
    server.cpp \
    SQlabel.cpp \
    SQHttpClient.cpp
QT           += network widgets

FORMS += \
    mainwindow.ui
