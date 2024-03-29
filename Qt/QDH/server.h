#pragma once
#include <QObject>
#include "../QLibrary/DataTable.h"
#include "../QLibrary/HttpRequest.h"
#include "../QLibrary/HttpServer.h"
#include "../QLibrary/HttpServer2.h"
#include "QDateTime"
#include "QTimer"
#include "dbmanager.h"

#define SERVER_VER "1.12.b"

class ServerDH : public QObject
{
    Q_OBJECT

public:
    ServerDH(bool runPrograms);
    ~ServerDH();

private:
    DataTable dr;    
    DbManager m_DbManager;

    bool m_running = true;
    bool m_runPrograms;

    int winter()
    {
        return month()<=4 || month()>=10;
    }
    int summer()
    {
        return (month()>=5 && month()<=8);
    }
    int month()
    {
        return QDateTime::currentDateTime().date().month();
    }
    int day()
    {
        return QDateTime::currentDateTime().date().day();
    }
    int hour()
    {
        return QDateTime::currentDateTime().time().hour();
    }
    int minute()
    {
        return QDateTime::currentDateTime().time().minute();
    }

    QElapsedTimer t_DbLog;
    QElapsedTimer t_PushWebData;
    QElapsedTimer t_BoilerACS;
    QElapsedTimer t_ExternalLight;
    QElapsedTimer t_evRooms;
    QElapsedTimer t_WinterFIRE;
    QElapsedTimer t_PDC;
    QElapsedTimer t_Camino;

    QElapsedTimer t_InternetConnection;
    QElapsedTimer t_Remote212;
    QElapsedTimer t_Remote216;

public:
    void Stop(){m_running = false; }

public:
    void manage_Progs(bool immediate);

    void manage_DbLog(int sec);
    void manage_PushWebData(int sec);

    void manage_BoilerACS(int sec);
    void manage_ExternalLight(int sec);
    void manage_EvRooms(int sec);
    void manage_PDC(int sec);
    void manage_Pumps(int sec);

    void manage_Remote210_Internet(int sec);
    void manage_Remote212_Freezer(int sec);
    void manage_Remote216_Christmas(int sec);

public slots:
    void run();

signals:
    void finished();
    void error(QString err);
    void updateValues(DataTable *v);

signals:
    void tickWatchdog();
};

