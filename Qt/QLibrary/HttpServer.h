#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThreadPool>
#include "DataTable.h"


class CQHttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CQHttpServer(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~CQHttpServer();

    DataValues *m_dv;

Q_SIGNALS:
    void closed();

private Q_SLOTS:

public:
    void startServer(DataValues *dv);

protected:
    void incomingConnection( qintptr handle );

private:
    QThreadPool *m_pool;
    quint16 m_port;
    bool m_debug;
};

