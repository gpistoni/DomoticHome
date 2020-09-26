#pragma once
#include <QObject>
#include "../QLibrary/DataTable.h"
#include "QDateTime"
#include "QTimer"
#include "dbevents.h"

#define SERVER_VER "1.6.6"

class ServerDH : public QObject
{
    Q_OBJECT

public:
    ServerDH(bool runPrograms);
    ~ServerDH();

private:
    DataTable dr;    
    dbEvents m_dbEvents;

    bool m_running = true;
    bool m_runPrograms;

    int winter()
    {
        return month()<=4 || month()>=10;
    }
    int summer()
    {
        return (month()>=6 && month()<=8);
    }
    int month()
    {
        return QDateTime::currentDateTime().date().month();
    }
    int hour()
    {
        return QDateTime::currentDateTime().time().hour();
    }
    int minute()
    {
        return QDateTime::currentDateTime().time().minute();
    }

    QElapsedTimer t_UpdateValues;
    QElapsedTimer t_DbLog;
    QElapsedTimer t_BoilerACS;
    QElapsedTimer t_ExternalLight;
    QElapsedTimer t_evRooms;
    QElapsedTimer t_WinterFIRE;
    QElapsedTimer t_PDC;
    QElapsedTimer t_Camino;

    QElapsedTimer t_InternetConnection;
    QElapsedTimer t_Remote212;

public:
    void Stop(){m_running = false; }

public:
    void manage_Progs(bool immediate);

    void manage_DbLog(int sec);
    void manage_BoilerACS(int sec);
    void manage_ExternalLight(int sec);
    void manage_evRooms(int sec);
    void manage_PDC(int sec);
    void manage_Pumps(int sec);

    void manage_Internet(int sec);
    void manage_Remote212(int sec);

public slots:
    void run();

signals:
    void finished();
    void error(QString err);
    void updateValues(DataTable *v);
};

