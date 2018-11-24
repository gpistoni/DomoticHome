#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThreadPool>


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
    void startServer();

protected:
    void incomingConnection( qintptr handle );

private:
    QThreadPool *m_pool;
    quint16 m_port;
    bool m_debug;

};

