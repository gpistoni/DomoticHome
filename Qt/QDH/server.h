#ifndef CWORKER_H
#define CWORKER_H

#include <QObject>
#include "../QLibrary/DataTable.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(bool runserver);
    ~Server();

    bool m_running = true;
     bool m_runServer;

public slots:
    void run();

signals:
    void finished();
    void error(QString err);
    void updateValues(DataTable *v);
};


#endif // CWORKER
