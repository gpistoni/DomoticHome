#include "server.h"
#include "../QLibrary/DataTable.h"
#include "QThread"


// --- CONSTRUCTOR ---
Server::Server(bool runPrograms) :
    m_runPrograms(runPrograms){
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Server::~Server() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Server::run()
{
    while (m_running)
    {
        /////////////////////////////////////////////////////////////////////////////////////////
        DataTable dr("192.168.1.200", 80);
        dr.ReadData();
        qDebug() << "DataReaded";

        ////////////////////////////////////////////////////////////////////////////////////////
        dr.wConsumed += dr.wL1;
        dr.wConsumed += dr.wL2;
        dr.wConsumed += dr.wL3;
        dr.wSurplus += dr.wProduced;
        dr.wSurplus -= dr.wConsumed;

        // remove-------------------------------------------
        float val[6];
        val[0]= dr.GetValueF("T6", "v0");
        val[1]= dr.GetValueF("T6", "v1");
        val[2]= dr.GetValueF("T6", "v2");
        val[3]= dr.GetValueF("T6", "v3");
        val[4]= dr.GetValueF("T6", "v4");
        val[5]= dr.GetValueF("T6", "v5");

        float produced = val[1];
        float consumed = val[2]+val[3]+val[4];
        float surplus = produced - consumed;

        dr.SetValue("T6", "Produced", produced);
        dr.SetValue("T6", "Consumed", consumed);
        dr.SetValue("T6", "Surplus", surplus);

        dr.SetValue("T6", "L1", val[2]);
        dr.SetValue("T6", "L2", val[3]);
        dr.SetValue("T6", "L3", val[4]);
        // remove-------------------------------------------

        qDebug () << "UpdatedValues";
        emit updateValues( &dr );
        ////////////////////////////////////////////////////////////////////////////////////////

        if (m_runPrograms)
        {

        }
        QThread::sleep(1);  //seconds
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // allocate resources using new here
    emit finished();
}
