#include "worker.h"
#include "../QLibrary/DataReader.h"

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
    /////////////////////////////////////////////////////////////////////////////////////////
    DataReader DR("192.168.1.200", 80);
    DR.ReadData();

    qDebug() << "PROVA: " << DR.GetValue("T6", "v1").toString();
    /////////////////////////////////////////////////////////////////////////////////////////

    emit update( &DR );

    /////////////////////////////////////////////////////////////////////////////////////////
    // allocate resources using new here
    qDebug("Hello World!");
    emit finished();
}
