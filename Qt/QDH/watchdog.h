#pragma once
#include <QObject>
#include "QDateTime"
#include "QTimer"
#include "dbmanager.h"

class Watchdog : public QTimer
{
    Q_OBJECT

public:
    Watchdog();

    ~Watchdog();

private:
    DataTable dr;
    QDateTime m_dtime;

    bool m_running = true;

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

public slots:
    void run();
    void tick();

public:
    void Stop(){ m_running = false; }

signals:
    void finished();
    void error(QString err);
};

