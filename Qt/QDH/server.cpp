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
        dr.LogMessage("DataReaded");

        ////////////////////////////////////////////////////////////////////////////////////////
        // calcoli
        dr.wConsumed += dr.wL1;
        dr.wConsumed += dr.wL2;
        dr.wConsumed += dr.wL3;
        dr.wSurplus += dr.wProduced;
        dr.wSurplus -= dr.wConsumed;

        dr.LogMessage(" UpdatedValues");
        emit updateValues( &dr );
        ////////////////////////////////////////////////////////////////////////////////////////

        if (m_runPrograms)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////
        //Send Changed
        dr.SendData();

        QThread::sleep(1);  //seconds
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // allocate resources using new here
    emit finished();
}

