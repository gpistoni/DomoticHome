#ifndef DBMANAGER_H
#define DBMANAGER_H
#include "../QLibrary/DataTable.h"
#include "QString"

class DbManager
{
private:
    DataTable *m_dt;

public:
    DbManager();

    void Init(DataTable *dt)
    {
        m_dt = dt;
    }

    void LogEnergy();

};

#endif // DBMANAGER_H
