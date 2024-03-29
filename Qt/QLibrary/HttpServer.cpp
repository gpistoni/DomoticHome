//#include "HttpServer.h"
//#include "HttpParser.h"
//#include "QtWebSockets/qwebsocketserver.h"
//#include "QtWebSockets/qwebsocket.h"
//#include <QtCore/QDebug>


//CQHttpServer::CQHttpServer(quint16 port, bool debug, QObject *parent) :
//    QTcpServer(parent),
//    m_dv(nullptr),
//    m_port(port),
//    m_debug(debug)
//{
//    m_pool = new QThreadPool(this);
//    m_pool->setMaxThreadCount(5);
//}

//void CQHttpServer::startServer( DataValues *dv)
//{
//    m_dv = dv;
//    if(this->listen(QHostAddress::Any, m_port))
//    {
//        qDebug() << "Server started port " << this->serverPort();
//    }
//    else
//    {
//        qDebug() << "Server did not start!";
//    }
//}

//CQHttpServer::~CQHttpServer()
//{
//}

//void CQHttpServer::incomingConnection(qintptr handle)
//{
//    // 1. QTcpServer gets a new connection request from a client.
//    // 2. It makes a task (runnable) here.
//    // 3. Then, the server grabs one of the threads.
//    // 4. The server throws the runnable to the thread.

//    qDebug() << "IncomingConnection: " << handle;

//    // Note: Rannable is a task not a thread
//    CHTTPParser *task = new CHTTPParser(m_dv);
//    task->setAutoDelete(true);

//    task->socketDescriptor = handle;

//    m_pool->start(task);
//    qDebug() << "pool started";
//}
