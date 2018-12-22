#pragma once

#include <QObject>
#include "../QLibrary/DataTable.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(bool runPrograms);
    ~Server();

    bool m_running = true;
    bool m_runPrograms;

public slots:
    void run();

signals:
    void finished();

    void error(QString err);
    void updateValues(DataTable *v);
};

