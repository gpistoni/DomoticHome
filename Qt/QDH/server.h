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

    int winter()
    {
        return month()<=4 || month()>=11;
    }
    int summer()
    {
        return month()>=6 && month()<=9;
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
    QElapsedTimer t_BoilerACS;
    QElapsedTimer t_ExternalLight;
    QElapsedTimer t_evRooms;
    QElapsedTimer t_WinterFIRE;
    QElapsedTimer t_WinterPDC;
    QElapsedTimer t_SummerPDC;
    QElapsedTimer t_Camino;

public:
    void Stop(){m_running = false; }

public:
    void manage_Progs(bool immediate);

    void manage_BoilerACS(int sec);
    void manage_ExternalLight(int sec);
    void manage_evRooms(int sec);
    void manage_WinterPDC(int sec);
    void manage_WinterFIRE(int sec);
    void manage_SummerPDC(int sec);
    void manage_Camino(int sec);

public slots:
    void run();

signals:
    void finished();
    void error(QString err);
    void updateValues(DataTable *v);
};

