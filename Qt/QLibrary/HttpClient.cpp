#include "HttpClient.h"
#include <QtNetwork/QHttpPart>
#include <QThread>
#include <iostream>
#include <QProcess>


CQHttpClient::CQHttpClient( QString serverName, quint16 serverPort, qint32 timeout )
{
    m_serverName = serverName;
    m_serverPort = serverPort;
    m_timeout = timeout;

    try
    {
        m_socket= new QTcpSocket(this);
        m_socket->connectToHost(m_serverName, m_serverPort);
        if (!m_socket->waitForConnected(m_timeout))
        {
            QString s = errorString();
        }
        // else
        //qDebug("Connected");
    }
    catch (...)
    {
        qDebug( "Socket Client Error" );
    }
}

CQHttpClient::~CQHttpClient(void)
{
    try
    {
        m_socket->disconnect();
        //m_socket->waitForDisconnected(1000);
        delete m_socket;
    }
    catch (...)
    {
        qDebug( "Socket Client Error" );
    }
}

QString CQHttpClient::Write(const QString &request, int timeout)
{
    //qDebug() << "_REQ_" + request;
    QString result;
    {
        //write the data
        m_socket->write( request.toUtf8() );
        m_socket->waitForBytesWritten(1000);

        //read answer
        m_socket->waitForReadyRead( timeout );
        while(m_socket->bytesAvailable() > 0)
        {
            result.append(m_socket->readAll());
            m_socket->waitForReadyRead( timeout );
        }
    }
    //qDebug() << "_RES_" + result;
    return result;
}

QString CQHttpClient::HTTPRequest(QString req, bool debugLog)
{
    try
    {
        QString sMsg = QString("GET ") + req + " HTTP/1.1\r\n" +
                "Host: " + m_serverName + "\r\n" +
                "Connection: keep-alive\r\n\r\n";
        if (debugLog)
            qDebug() << QString("GET ") + req;
        return  Write( sMsg.toUtf8() );
    }
    catch (...)
    {
        return "";
    }
}

QString CQHttpClient::Request_Json()
{
    return HTTPRequest( QString("json"));
}

QString CQHttpClient::Request(QString path)
{
    return HTTPRequest( QString("/") + path, false );
}

bool CQHttpClient::PingGoogle(QString &out)
{
    QProcess process;
    process.start("ping -c1 -s1 -w1 www.google.com");
    process.waitForFinished(5000);

    out = process.readAllStandardOutput();
    out += process.readAllStandardError();

    if (out.contains("1 received"))
        return true;
    return false;
}


