#include "server.h"
#include "../QLibrary/DataTable.h"
#include "QThread"


// --- CONSTRUCTOR ---
Server::Server(bool runPrograms) :
    dr("192.168.1.200", 80),
    m_runPrograms(runPrograms)
{
    t_UpdateValues.start();
    t_BoilerACS.start();
    t_ExternalLight.start();
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
        try {
            while (m_running)
            {
                QThread::msleep(100);  //milliseconds

                if ( t_UpdateValues.elapsed() < 1000 )
                    continue;
                t_UpdateValues.restart();

                /////////////////////////////////////////////////////////////////////////////////////////
                dr.ReadData();

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
                // forced
                dr.progBoilerACS.Value(true);
                dr.progExternalLight.Value(true);

                if (m_runPrograms)
                {
                    manage_BoilerACS();
                    manage_ExternalLight(60);
                }
                ////////////////////////////////////////////////////////////////////////////////////////
                //Send Changed
                bool modifiedProg = dr.SendModifiedData();

                if (modifiedProg)
                {
                   manage_BoilerACS();
                   manage_ExternalLight(1);
                }
            }

            /////////////////////////////////////////////////////////////////////////////////////////
            // allocate resources using new here
            emit finished();
        } catch (...)
        {
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_BoilerACS()
{
    if ( t_BoilerACS.elapsed() < 10000 )
        return;
    t_BoilerACS.restart();

    dr.LogMessage(">> ------------------- BoilerACS_Manager --------------- >>");

    bool boilerACS = false;
    /**************************************************************************************************/
    if ( dr.progBoilerACS )
    {
        //decido se accendere il boiler se ho un surplus di energia
        if ( (dr.rBoilerACS && dr.wSurplus > 100) ||
             (!dr.rBoilerACS && dr.wSurplus > 600) )
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }
        //decido se accendere il boiler solo a mezzogiorno e solo se il camino non funziona
        if ( hour() > 12 && hour() < 16  )
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON hour:" + QString::number( hour() ) + " >12 & <16");
        }
        if ( dr.tReturnFireplace > 30 )
        {
            boilerACS = false;
            dr.LogMessage("Condizione OFF DT.ReturnFireplace:" + dr.tReturnFireplace.svalue() + "> 30");
        }
    }
    /**************************************************************************************************/
    // boiler
    dr.LogMessage("BoilerACS [" + QString::number( boilerACS ) + "]");
    dr.rBoilerACS.ModifyValue( boilerACS );
    dr.LogMessage("<<< BoilerACS_Manager <<<");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_ExternalLight(int sec)
{
    if ( t_ExternalLight.elapsed() < sec * 1000 )
        return;
    t_ExternalLight.restart();

    dr.LogMessage(">>-------------------- ExternalLight_Manager -------------------->>");

    bool lightSide = false;
    bool lightLamp = false;

    if (dr.progExternalLight)
    {
        /**************************************************************************************************/
        dr.LogMessage("-- darkExternal: " + dr.darkExternal.svalue() + " Request [" + QString::number( 32 - 1 * dr.lampLati ) + "]" );
        if ( dr.darkExternal > 32 - 1 * dr.lampLati ) // isteresi
        {
            lightSide = true;
            lightLamp = true;
        }

        /**************************************************************************************************/
        dr.LogMessage("-- LightLamp [" +  QString::number(lightLamp) + "]  LightSide [" +  QString::number(lightSide) + "]" );
    }

    // attuatori
    dr.lampAngoli.ModifyValue(lightSide);
    dr.lampLati.ModifyValue(lightSide);
    dr.lampPalo.ModifyValue(lightLamp);
    dr.lampExtra.ModifyValue(lightLamp);

    dr.LogMessage("<<< ExternalLight_Manager <<<");
}

