#pragma once
#include <QObject>
#include <QRunnable>
#include "DataTable.h"

class CHTTPParser: public QRunnable
{
public:
    CHTTPParser(DataValues *dv);

    DataValues *m_dv;

protected:
    void run();
    void S_page_all(QTcpSocket *socket);
    void S_header(QTcpSocket *socket);

public:
    qintptr socketDescriptor;
};
