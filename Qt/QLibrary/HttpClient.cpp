#include "HttpClient.h"
#include <QtNetwork/QHttpPart>
#include <QThread>
#include <iostream>


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
        return"";
    }
}

QString CQHttpClient::Request_Get(QString path)
{
    return HTTPRequest( QString("/") + path, true );
}

QString CQHttpClient::Request_Json()
{
    return HTTPRequest( QString("json"));
}

QString CQHttpClient::Request_Set(QString path)
{
    return HTTPRequest( QString("/") + path, true );
}

bool CQHttpClient::PingGoogle()
{
    if (system("ping -c1 -s1 www.google.com"))
    {
        std::cout<<"There is no internet connection \n";
        return false;
    }
    std::cout<<"There is internet connection available\n";
    return true;


    //    CURL *curl;
    //    CURLcode res;

    //    curl = curl_easy_init();
    //    if(curl)
    //    {
    //        curl_easy_setopt(curl, CURLOPT_URL, "www.google.com");
    //        while ((res = curl_easy_perform(curl)) != CURLE_OK)
    //        {
    //            switch (res)
    //            {
    //            case CURLE_COULDNT_CONNECT:
    //            case CURLE_COULDNT_RESOLVE_HOST:
    //            case CURLE_COULDNT_RESOLVE_PROXY:
    //                return false;
    //                break;
    //            default:
    //                cerr<<"Request failed:"<<curl_easy_strerror(res)<<endl;
    //                exit(1);
    //            }
    //        }


    //        /* always cleanup */
    //        curl_easy_cleanup(curl);
    //        return true;
    //    }
}


