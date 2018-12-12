#include "worker.h"
#include "../QLibrary/DataTable.h"
#include "QThread"


// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Worker::process()
{
    while (1)
    {
        /////////////////////////////////////////////////////////////////////////////////////////
        DataTable dr("192.168.1.200", 80);
        dr.ReadData();

        ////////////////////////////////////////////////////////////////////////////////////////
        double val[6];
        val[0]= dr.GetValueF("T6", "v0");
        val[1]= dr.GetValueF("T6", "v1");
        val[2]= dr.GetValueF("T6", "v2");
        val[3]= dr.GetValueF("T6", "v3");
        val[4]= dr.GetValueF("T6", "v4");
        val[5]= dr.GetValueF("T6", "v5");

        double produced = val[1];
        double consumed = val[2]+val[3]+val[4];
        double surplus = produced - consumed;

        dr.SetValue("T6", "Produced", produced);
        dr.SetValue("T6", "Consumed", consumed);
        dr.SetValue("T6", "Surplus", surplus);

        dr.SetValue("T6", "L1", val[2]);
        dr.SetValue("T6", "L2", val[3]);
        dr.SetValue("T6", "L3", val[4]);

        emit updateValues( &dr );
        QThread::sleep(1);
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    // allocate resources using new here
    qDebug("Hello World!");
    emit finished();
}
