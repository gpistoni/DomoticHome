#include "SQHttpClient.h"
#include <QtCore\QThread>
#include <QtNetwork/QHttpPart>
#include <QBitmap>

QString  CSQHttpClient::m_serverName;
quint16  CSQHttpClient::m_serverPort;
qint32   CSQHttpClient::m_timeout;
QElapsedTimer CSQHttpClient::Timer;

CSQHttpClient::CSQHttpClient()
{
    try
    {
        m_socket= new QTcpSocket(this);
        m_socket->connectToHost(m_serverName, m_serverPort);
        if (!m_socket->waitForConnected(m_timeout))
        {
            QString s = errorString();
        }
    }
    catch (...)
    {
        qDebug( "Socket Client Error" );
    }
}

CSQHttpClient::~CSQHttpClient(void)
{
    try
    {
        m_socket->disconnect();
        m_socket->waitForDisconnected(1000);
        delete m_socket;
    }
    catch (...)
    {
        qDebug( "Socket Client Error" );
    }
}

QString CSQHttpClient::Write(const QString &request, int timeout)
{
    //qDebug() << "_REQ_" + request;

    QByteArray buffer;
    {
        //write the data
        m_socket->write( request.toUtf8() );
        m_socket->waitForBytesWritten();

        //read answer
        m_socket->waitForReadyRead( timeout );
        while (  m_socket->bytesAvailable() > 0 )
        {
            buffer = m_socket->readAll();
        }
    }
    //qDebug() << "_RES_" + QString(buffer).toLatin1();
    return QString(buffer);
}

QString CSQHttpClient::HTTPRequest(QString path)
{
    try
    {
        QString sMsg;
        sMsg = "GET /";
        sMsg += path;
        return  Write( sMsg.toUtf8() );
    }
    catch (...)
    {
        return"";
    }
}


