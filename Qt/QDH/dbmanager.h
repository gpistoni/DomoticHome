#ifndef DBMANAGER_H
#define DBMANAGER_H
#include "../QLibrary/DataTable.h"
#include "QString"
#include <QThread>

class DbManager: public QThread
{
private:
    DataTable   *m_dt;

public:
    DbManager();
    virtual ~DbManager()
    {
        quit();
    }

    void Init(DataTable *dt)
    {
        m_dt = dt;
        start();
    }

    void LogEnergy();

private:
    void run()
    {
        // ...
        m_dt->LogMessage("DbManager THREAD");
    }

};

#endif // DBMANAGER_H
