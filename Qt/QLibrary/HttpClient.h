#pragma once
#include <QTcpSocket>
#include <QElapsedTimer>

class CQHttpClient : public QObject
{
    QTcpSocket *m_socket;

    QString  m_serverName;
    quint16  m_serverPort;
    qint32   m_timeout;

public:
    static QElapsedTimer Timer;

public:
    CQHttpClient( QString serverName, quint16 serverPort, qint32 timeout );
    virtual ~CQHttpClient(void);

    QString errorString()
    {
        return m_socket->errorString().toUtf8().constData();
    }

private:
    QString Write(const QString &str, int timeout = 3000 );

private:
    QString HTTPRequest(QString path, bool debugLog = false);

public:
    QString Request_Get(QString path );
    QString Request_Json();
    QString Request_Set(QString path);

    static bool PingGoogle(QString &out);
};



