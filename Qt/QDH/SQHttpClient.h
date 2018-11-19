#pragma once
#include "QtNetwork/qtcpsocket.h"
#include "qnetworkreply.h"
#include <QImage>
#include <QElapsedTimer>


class CSQHttpClient : public QObject
{
    QTcpSocket *m_socket;

    static QString  m_serverName;
    static quint16  m_serverPort;
    static qint32   m_timeout;

public:
    static QElapsedTimer Timer;

public:
    CSQHttpClient();

    virtual ~CSQHttpClient(void);


    QString errorString()
    {
        return m_socket->errorString().toUtf8().constData();
    }

public:
    static void Setup( QString serverName, quint16 serverPort, qint32 timeout )
    {
        m_serverName = serverName;
        m_serverPort = serverPort;
        m_timeout = timeout;
    }

private:
    QString Write(const QString &str, int timeout = 3000 );
    void Write2ByteArray(const QString &st, QByteArray &response, bool hasHttpHeader, int timeout = 3000 );


 private:
    QString HTTPRequest( QString path );

 public:
    void GetImage( QString path, QImage &dest);
    void GetStream( QString path, QByteArray &dataBMP);


public:
    static QString GetValue( QString path )
    {
        CSQHttpClient Client;
        return Client.HTTPRequest( QString("get?") + path );
    }

    static QString GetValue_Json()
    {
        CSQHttpClient Client;
        return Client.HTTPRequest( QString("json"));
    }
};


