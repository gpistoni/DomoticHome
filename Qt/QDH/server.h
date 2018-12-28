#pragma once

#include <QObject>
#include "../QLibrary/DataTable.h"
#include "QDateTime"
#include "QTimer"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(bool runPrograms);
    ~Server();

private:
    DataTable dr;

    bool m_running = true;
    bool m_runPrograms;

    int hour()
    {
        return QDateTime::currentDateTime().time().hour();
    }
    int minute()
    {
        return QDateTime::currentDateTime().time().minute();
    }

    QElapsedTimer t_UpdateValues;
    QElapsedTimer t_BoilerACS;
    QElapsedTimer t_ExternalLight;
    QElapsedTimer t_Winter;
    QElapsedTimer t_Summer;

public:
    void Stop(){m_running = false; }

public slots:
    void manage_BoilerACS();
    void manage_ExternalLight(int sec);
    void manage_Winter(int sec);
    void manage_Summer(int sec);

    void run();

signals:
    void finished();
    void error(QString err);
    void updateValues(DataTable *v);
};

