#include "HttpServer.h"
#include "HttpServer2.h"
#include "HttpParser.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QDataStream>

//SocketThread::SocketThread(qintptr descriptor, QObject *parent)
//    :  QThread(parent), m_descriptor(descriptor)
//{
//}

//SocketThread::~SocketThread()
//{
//}

//void SocketThread::run()
//{
//    qDebug() << Q_FUNC_INFO;
//    m_socket = new QTcpSocket;
//    m_socket->setSocketDescriptor(m_descriptor);

//    connect(m_socket, SIGNAL(readyRead()),    this, SLOT(onReadyRead()), Qt::DirectConnection);
//    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);

//    exec();
//}

/*
void HTTPThread::run()
{
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    qDebug() << text;
    tcpSocket.write(text.toLatin1(), text.length());
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
*/


//void SocketThread::onConnected()
//{
//    qDebug() << "onConnected";
//}

//void SocketThread::onReadyRead()
//{
//    qDebug() << "onReadyRead";

//    QDataStream in(m_socket);
//    in.setVersion(QDataStream::Qt_5_5);

//    QString message;
//    in >> message;
//    qDebug() << message;

//    m_socket->disconnectFromHost();
//}

//void SocketThread::onDisconnected()
//{
//    qDebug() << "onDisconnected";
//    m_socket->close();
//    // Exit event loop
//    quit();
//}

//CQHttpServer::CQHttpServer(quint16 port, bool debug, QObject *parent):
//    QTcpServer(parent),
//    m_port(port)
//{
//    if (this->listen(QHostAddress::Any, m_port)) {
//        qDebug() << "HTTP Server started port : " << this->serverPort();
//    } else {
//        qDebug() << "HTTP Server did not start";
//    }
//}

//void CQHttpServer::incomingConnection(qintptr handle)
//{
//    qDebug() << Q_FUNC_INFO << " new connection";
//    SocketThread *socket = new SocketThread(handle);

//    connect(socket, SIGNAL(finished()), socket, SLOT(deleteLater()));
//    socket->start();
//}

/*
CQHttpServer::CQHttpServer(quint16 port, bool debug, QObject *parent) :
    QTcpServer(parent),
    m_dv(nullptr),
    m_port(port),
    m_debug(debug),
    m_Thread(nullptr)
{}

void CQHttpServer::startServer( DataValues *dv)
{
    m_dv = dv;
    if ( this->listen(QHostAddress::Any, m_port))
    {
        qDebug() << "HTTP Server started port " << m_port;
    }
    else
    {
        qDebug() << "HTTP Server did not start!";
    }
    m_Thread = new QThread();
    m_Thread->start();
}

CQHttpServer::~CQHttpServer()
{
    if (m_Thread!=nullptr)    delete m_Thread;
}

void CQHttpServer::incomingConnection(qintptr socketDescriptor)
{
    // 1. QTcpServer gets a new connection request from a client.
    // 2. It makes a task (runnable) here.
    // 3. Then, the server grabs one of the threads.
    // 4. The server throws the runnable to the thread.

    qDebug() << "IncomingConnection: " << socketDescriptor;

    // Note: Rannable is a task not a thread
    CHTTPParser *task = new CHTTPParser(m_dv);
    //task->moveToThread(m_Thread);
    //clients->append(task);
}
*/


/////////////////////////////////////////////////////////////////////////////////////////
HTTPServer::HTTPServer(QObject *parent)
    : QTcpServer(parent)
{
    if (!listen(QHostAddress::Any, 8080))
    {
        qDebug() << "Unable to start the server:" << errorString();
    }

    qDebug() << "The server is running on port:" << serverPort();

}

void HTTPServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "IncomingConnection";
    QString content;
    content = "<p><a href='on'><button>ON</button>";
    content += "\n";

    QString header;
    header += "HTTP/1.1 200 OK \r\n";
    header += "Content-Type: text/html \r\n";
    header += "\r\n";

    m_thread = new HTTPThread(socketDescriptor, header + content, this);
    connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));
    m_thread->start();
}

/////////////////////////////////////////////////////////////////////////////////////////
HTTPThread::HTTPThread(qintptr socketDescriptor, QString fortune, QObject *parent)
    : QThread(parent),
      socketDescriptor(socketDescriptor),
      text(fortune)
{}

void HTTPThread::run()
{
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    qDebug() << text;
    tcpSocket.write(text.toLatin1(), text.length());
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}

