#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThreadPool>
#include "DataTable.h"

#include <QThread>
#include <QObject>

//class SocketThread: public QThread
//{
//    Q_OBJECT
//public:
//    SocketThread(qintptr descriptor, QObject *parent = 0);
//    ~SocketThread();

//protected:
//    void run() Q_DECL_OVERRIDE;

//private slots:
//    void onConnected();
//    void onReadyRead();
//    void onDisconnected();

//private:
//    QTcpSocket *m_socket;
//    qintptr m_descriptor;
//};

//class CQHttpServer: public QTcpServer
//{
//public:
//    DataValues *m_dv;
//    quint16 m_port;

//public:
//    CQHttpServer(quint16 port = 8080, bool debug = false, QObject *parent = 0);
//    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
//};

/*
class CQHttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CQHttpServer(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~CQHttpServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:

public:
    void startServer(DataValues *dv);

protected:
    void incomingConnection( qintptr handle ) Q_DECL_OVERRIDE;

private:
    QThread *m_Thread;
    quint16 m_port;
    bool m_debug;
};
*/

#include <QStringList>
#include <QTcpServer>

 class HTTPThread;

/////////////////////////////////////////////////////////////////////////////////////////
class HTTPServer : public QTcpServer
{
    Q_OBJECT

public:
    HTTPServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:
    HTTPThread *m_thread;
};

/////////////////////////////////////////////////////////////////////////////////////////
 class HTTPThread : public QThread
{
    Q_OBJECT

public:
    HTTPThread(qintptr socketDescriptor, QString fortune, QObject *parent);

    void run() Q_DECL_OVERRIDE;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};


