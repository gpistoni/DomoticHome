#include "watchdog.h"
#include "../QLibrary/DataTable.h"
#include "QThread"
#include "QFile"

// --- PROCESS ---
// Start processing data.
Watchdog::Watchdog():
    dr("192.168.1.200", 80)
{
    m_dtime = QDateTime::currentDateTime();
    m_running = true;
    setInterval(10000);
}

Watchdog::~Watchdog()
{
}

// -- RUN --
void Watchdog::run()
{
    dr.LogMessage("WATCHDOG");

    if ( m_dtime.secsTo(QDateTime::currentDateTime()) > 600)
    {
        dr.LogMessage("****** CRITICAL ******");
        dr.LogMessage("** Watchdog TIMEOUT **");
        dr.LogMessage("****** EXIT **********");
        QThread::sleep(1);
        exit(-1);
    }
}

void Watchdog::tick()
{
    m_dtime = QDateTime::currentDateTime();
    dr.LogMessage("Watchdog TICK");
}

