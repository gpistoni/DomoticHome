#include "server.h"
#include "../QLibrary/DataTable.h"
#include "../QLibrary/HttpServer.h"
#include "QThread"
#include "QFile"
#include <unistd.h>


// --- CONSTRUCTOR ---
Server::Server(bool runPrograms) :
    dr("192.168.1.200", 80),
    m_runPrograms(runPrograms)
{
    t_UpdateValues.start();
    t_InternetConnection.start();
    t_BoilerACS.start();
    t_ExternalLight.start();
    t_evRooms.start();
    t_PDC.start();
    t_WinterFIRE.start();
    t_Camino.start();
}

// --- DECONSTRUCTOR ---
Server::~Server() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Server::run()
{
    CQHttpServer HttpServer(8080);
    HttpServer.startServer(&dr);

    bool firstRun = true;
    while (m_running)
    {
        dr.LogMessage("VER 1.1.4", true);

        // forced by date
        dr.progBoilerACS.ModifyValue(true);
        dr.progExternalLight.ModifyValue(true);
        dr.progSummerPDC.ModifyValue(false);

        if ( winter() )
        {
            dr.progWinterFIRE.ModifyValue(true);
            dr.progWinterPDC.ModifyValue(true);
            dr.progSummerPDC.ModifyValue(false);
            dr.progSummerPDC_eco.ModifyValue(false);
        }
        if ( summer() )
        {
            dr.progWinterFIRE.ModifyValue(false);
            dr.progWinterPDC.ModifyValue(false);
            dr.progSummerPDC_eco.ModifyValue(true);
        }

        try {
            while (m_running)
            {
                QThread::msleep(500);  //milliseconds

                if (!firstRun && !m_runPrograms)
                {
                    if (t_UpdateValues.elapsed() < 3000 ) continue;
                }
                t_UpdateValues.restart();

                /////////////////////////////////////////////////////////////////////////////////////////
                dr.ReadData();

                dr.wProduced.m_value *= 1.15f;

                // calcoli
                dr.wConsumed += dr.wL1;
                dr.wConsumed += dr.wL2;
                dr.wConsumed += dr.wL3;

                dr.wSurplus = dr.wProduced;
                dr.wSurplus -= dr.wConsumed;

                dr.LogPoint();
                emit updateValues( &dr );

                ////////////////////////////////////////////////////////////////////////////////////////
                if (firstRun)
                {
                    manage_Progs(true);
                }

                ////////////////////////////////////////////////////////////////////////////////////////
                if (m_runPrograms)
                {
                    manage_Progs(false);
                }

                ////////////////////////////////////////////////////////////////////////////////////////
                //Send Changed
                bool modifiedProg = dr.SendModifiedData();
                if (modifiedProg)
                {
                    manage_Progs(true);
                }
                  firstRun = false;
            }

            /////////////////////////////////////////////////////////////////////////////////////////
            // allocate resources using new here
            emit finished();
        }
        catch (...)
        {
            dr.LogMessage("catch");
        }
    }
}





void Server::manage_Progs(bool immediate)
{
    if (immediate)
    {
        manage_Internet(1);
        manage_ExternalLight(1);
        manage_BoilerACS(1);
        manage_WinterFIRE(1);
        manage_PDC(1);
        manage_evRooms(1);
        if ( winter() ) manage_Camino(1);
    }
    else
    {
        manage_Internet(2*60);
        manage_ExternalLight(10*60);
        manage_BoilerACS(10*60);
        manage_PDC(5*60);
        manage_WinterFIRE(3*60);
        manage_evRooms(3*60);
        if ( winter() )
            manage_Camino(3*60);
    }
}

void Server::manage_Internet(int sec)
{
    if ( t_InternetConnection.elapsed() < sec * 1000 ) return;
    t_InternetConnection.restart();

    bool connected = CQHttpClient::PingGoogle();
    dr.LogMessage("Ping Google:" + connected);

    if (!connected)
     {
        // off
        CQHttpClient client("192.168.1.210", 80, 10000 );
        client.Request_Set("OFF");
        sleep(5);
        client.Request_Set("ON");
     }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_BoilerACS(int sec)
{
    if ( t_BoilerACS.elapsed() < sec * 1000 ) return;
    t_BoilerACS.restart();

    dr.LogMessage("--- BoilerACS ---"  );

    bool boilerACS = false;
    /**************************************************************************************************/
    if ( dr.progBoilerACS )
    {
        if ( dr.rBoilerACS && dr.wSurplus > 50 ) // se e gia acceso
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }
        else if ( !dr.rBoilerACS && dr.wSurplus > 450 ) // se e spento
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }

        //decido se accendere il boiler solo a mezzogiorno
        if ( hour() > 12 && hour() < 16  )
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON hour:" + QString::number( hour() ) + " >12 & <16");
        }

        // solo se il camino non funziona
        if ( dr.tReturnFireplace > 30 )
        {
            boilerACS = false;
            dr.LogMessage("Condizione OFF ReturnFireplace:" + dr.tReturnFireplace.svalue() + "> 30");
        }
    }
    /**************************************************************************************************/
    // boiler
    dr.LogMessage("BoilerACS [" + QString::number( boilerACS ) + "]");
    dr.rBoilerACS.ModifyValue( boilerACS );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_ExternalLight(int sec)
{
    if ( t_ExternalLight.elapsed() < sec * 1000 ) return;
    t_ExternalLight.restart();

    dr.LogMessage(QDateTime::currentDateTime().date().toString() );
    dr.LogMessage("--- ExternalLight ---"  );

    bool lightSide = false;
    bool lightLamp = false;

    if (dr.progExternalLight)
    {
        if ( hour()>=17 || hour() <=7)
        {
            /**************************************************************************************************/
            dr.LogMessage("darkExternal: " + dr.darkExternal.svalue() + " Request >" + QString::number( 32 - 2 * dr.lampLati )  );
            if ( dr.darkExternal > (32 - 2 * dr.lampLati) ) // isteresi
            {
                lightSide = true;
                lightLamp = true;
            }

            if ( hour() <= 7 )
                lightLamp = false;
        }
    }

    dr.LogMessage("LightLamp [" +  QString::number(lightLamp) + "] " );
    dr.LogMessage("LightSide [" +  QString::number(lightSide) + "]" );

    // attuatori
    dr.lampAngoli.ModifyValue(lightSide);
    dr.lampLati.ModifyValue(lightSide);
    dr.lampPalo.ModifyValue(lightLamp);
    dr.lampExtra.ModifyValue(lightLamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  Server::manage_evRooms( int sec )
{
    if ( t_evRooms.elapsed() < sec * 1000 ) return;
    t_evRooms.restart();

    dr.LogMessage("--- EvRooms ---" );

    bool sala = false;
    bool sala2 = false;
    bool cucina = false;
    bool cameraS = false;
    bool cameraD = false;
    bool cameraD2 = false;
    bool cameraM = false;
    bool cameraM2 = false;

    bool allRoom = dr.progAllRooms;

    //attivo le stanze solo a determinate condizioni (INVERNO)
    if (dr.progWinterPDC || dr.progWinterFIRE || dr.progSummerPDC || dr.progSummerPDC_eco )
    {
        if ( (hour() >= 6 ) && (dr.rPompaPianoPrimo || dr.rPompaPianoTerra || dr.rPdcPompa || dr.tInputMixer > 30) )
        {
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accendere le stanze
            QString str = "Stanze:";
            if ( dr.tSala < dr.tSala.setPoint() )
            {
                str += " tSal " + dr.tSala.svalue()  + "<" + dr.tSala.ssetPoint();
                sala = true;
                sala2 = true;
            }
            if ( dr.tCucina < dr.tCucina.setPoint() )
            {
                str += " tCuc " + dr.tCucina.svalue()  + "<" + dr.tCucina.ssetPoint();
                cucina = true;
            }
            if ( dr.tCameraS < dr.tCameraS.setPoint() )
            {
                str += " tCamS " + dr.tCameraS.svalue()  + "<" + dr.tCameraS.ssetPoint();
                cameraS = true;
            }
            if ( dr.tCameraD < dr.tCameraD.setPoint() )
            {
                str += " tCamD " + dr.tCameraD.svalue()  + "<" + dr.tCameraD.ssetPoint();
                cameraD = true;
            }
            if ( dr.tCameraD < dr.tCameraD.setPoint(-2) )
            {
                cameraD2 = true;
            }
            if ( dr.tCameraM < dr.tCameraM.setPoint() )
            {
                str += " tCamM " + dr.tCameraM.svalue()  + "<" + dr.tCameraM.ssetPoint();
                cameraM = true;
            }
            if ( dr.tCameraM < dr.tCameraM.setPoint(-2) )
            {
                cameraM2 = true;
            }
            if ( dr.rPdc && dr.rPdcHeat )
            {
                str += "Pdc Heat mode";
                sala = true;
                cucina = true;
            }

            dr.LogMessage(str);
        }
    }
    //attivo le stanze solo a determinate condizioni (ESTATE)
    if (dr.progSummerPDC || dr.progSummerPDC_eco )
    {
        if ( dr.rPdcPompa || dr.rPompaPianoPrimo )
        {
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accendere le stanze
            QString str = "Stanze";
            if ( dr.tSala > dr.tSala.setPoint(2)  )
            {
                str += " tSala " + dr.tSala.svalue()  + ">" + dr.tSala.ssetPoint(2) ;
                sala = true;
                sala2 = true;
            }
            if ( dr.tCucina > dr.tCucina.setPoint(2)  )
            {
                str += " tCuc " + dr.tCucina.svalue()  + ">" + dr.tCucina.ssetPoint(2);
                cucina = true;
            }
            if ( dr.tCameraS > dr.tCameraS.setPoint(2) )
            {
                str += " tCamS " + dr.tCameraS.svalue()  + ">" + dr.tCameraS.ssetPoint(2);
                cameraS = true;
            }
            if ( dr.tCameraD > dr.tCameraD.setPoint(2)  )
            {
                str += " tCamD " + dr.tCameraD.svalue()  + ">" + dr.tCameraD.ssetPoint(2);
                cameraD = true;
            }
            if ( dr.tCameraD > dr.tCameraD.setPoint(3) )
            {
                cameraD2 = true;
            }
            if ( dr.tCameraM > dr.tCameraM.setPoint(2) )
            {
                str += " tCamM " + dr.tCameraM.svalue()  + ">" + dr.tCameraM.ssetPoint(2);
                cameraM = true;
            }
            if ( dr.tCameraM > dr.tCameraM.setPoint(2) )
            {
                cameraM2 = true;
            }

            dr.LogMessage(str);
        }
    }

    //**********************************************************************
    dr.LogMessage("EvRooms s[" +  QString::number(sala) + "] " );

    // elettrovalvole stanze -----------------------------------------------------------------------
    dr.evCameraM1.ModifyValue(cameraM || allRoom);
    dr.evCameraM2.ModifyValue(cameraM2 || allRoom);
    dr.evSala1.ModifyValue(sala || allRoom);
    dr.evSala2.ModifyValue(sala2 || allRoom );
    dr.evCucina.ModifyValue(cucina || allRoom );
    dr.evCameraS.ModifyValue(cameraS || allRoom );
    dr.evCameraD1.ModifyValue(cameraD || allRoom );
    dr.evCameraD2.ModifyValue(cameraD2 || allRoom);
}

/******************************************************************************************************************************************************************/
void  Server::manage_PDC( int sec )
{
    if ( t_PDC.elapsed() < sec * 1000 ) return;
    t_PDC.restart();

    dr.LogMessage("--- PDC SURPLUS ---" );

    bool needPdc = false;
    bool needPdc_Pump = false;
    bool needPdc_Night = true;
    bool needPdc_Heat = false;

    dr.LogMessage("PDC surplusW:" + dr.wSurplus.svalue() + " [L1]:" + dr.wL1.svalue() + " [L2]:" + dr.wL2.svalue() + " [L3]:" + dr.wL3.svalue());

    float surplus = dr.wSurplus;

    if (dr.progWinterPDC)
    {
        //////////////////////////////////////////////////////////////////////////////////
        //decido se accendere PDC
        if (dr.rPdc && dr.wSurplus > 50 )
        {
            dr.LogMessage("PDC ON SurplusW:" + dr.wSurplus.svalue() );
            needPdc = true;
        }
        else if (!dr.rPdc && dr.wSurplus > 600 )
        {
            dr.LogMessage("PDC ON SurplusW:" + dr.wSurplus.svalue() );
            needPdc = true;
        }

        //pdc Gia Accesa
        if (dr.rPdc && dr.wSurplus > 600 )
        {    // molto surplus
            dr.LogMessage("PDC Molto SurplusW:" + dr.wSurplus.svalue() );
            needPdc_Night = false;
        }
        if (dr.progAllRooms)
        {
            dr.LogMessage("PDC ON FORCED ALLROOMS");
            needPdc = true;
        }
        needPdc_Heat = needPdc;
        needPdc_Pump = needPdc;
    }
    else if (dr.progSummerPDC || dr.progSummerPDC_eco)
    {
        if (dr.progSummerPDC)
        {
            needPdc = true;
        }
        if (dr.progSummerPDC_eco)
        {
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accendere PDC
            if (dr.rPdc && surplus > 200 )
            {
                dr.LogMessage("PDC ON SurplusW:" + dr.wSurplus.svalue() );
                needPdc = true;
            }
            else if (!dr.rPdc && surplus > 800 )
            {
                dr.LogMessage("PDC ON SurplusW:" + dr.wSurplus.svalue() );
                needPdc = true;
            }
            if (dr.rPdc && dr.wSurplus > 600 )
            {    // molto surplus
                dr.LogMessage("PDC ON Molto SurplusW:" + dr.wSurplus.svalue() );
                needPdc_Night = false;
            }
        }

        /**************************************************************************************************/
        if (needPdc && dr.tExternal < 25 )  // minima t esterna
        {
            dr.LogMessage("PDC OFF t estrerna 25>" + dr.tExternal.svalue() );
            needPdc = false;
        }

        needPdc_Pump = needPdc;
        needPdc_Heat = false;

        /**************************************************************************************************/
        if (needPdc && dr.tInletFloor < 19 )  // minima t Acqua raffreddata
        {
            dr.LogMessage("PDC OFF t inlet " + dr.tInletFloor.svalue() + "< 19" );
            needPdc = false;
        }

        /**************************************************************************************************/
        if (needPdc && dr.tInletFloor+dr.tReturnFloor < 40 )  // minima t Acqua
        {
            dr.LogMessage("PDC OFF t inlet " + dr.tInletFloor.svalue() +"+"+dr.tReturnFloor.svalue() + "< 40" );
            needPdc = false;
        }
    }

    dr.LogMessage("NeedPdc: [" + QString::number(needPdc) + "]" );
    dr.LogMessage("NeedPdc_Night: [" + QString::number(needPdc && needPdc_Night) + "]" );
    dr.LogMessage("NeedPdc_Pump [" + QString::number(needPdc_Pump) + "]");
    dr.LogMessage("NeedPdc_Heat [" + QString::number(needPdc && needPdc_Heat) + "]");

    // comandi sulla centrale -----------------------------------------------------
    // accendo PDC
    dr.rPdc.ModifyValue( needPdc );
    // heat
    dr.rPdcHeat.ModifyValue( needPdc && needPdc_Heat );
    //pompa
    dr.rPdcPompa.ModifyValue( needPdc_Pump );
    dr.rPompaPianoPrimo.ModifyValue( needPdc_Pump );
    //night
    dr.rPdcNightMode.ModifyValue( needPdc && needPdc_Night );
}

/******************************************************************************************************************************************************************/
void  Server::manage_WinterFIRE( int sec )
{
    if ( t_WinterFIRE.elapsed() < sec * 1000 ) return;
    t_WinterFIRE.restart();

    dr.LogMessage("--- Winter FIRE ---"  );

    bool needPompa_pt = false;
    bool needPompa_pp = false;

    if (dr.progWinterFIRE)
    {
        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere/spegnere pompa piano primo
        needPompa_pp = true;
        if ( dr.tInputMixer < 27 && dr.tPufferHi < 28 && dr.tReturnFireplace < 28 )   // non ho temperatura
        {
            dr.LogMessage("Condizione Pompa PP insufficiente: tInletFloor: " + dr.tInletFloor.svalue() + " tReturnFloor: " + dr.tReturnFloor.svalue() );
            needPompa_pp = false;
        }
        if ( (dr.tReturnFloor > 29) )  // ritorno troppo alto - non ne ho bisogno
        {
            dr.LogMessage("Stop Pompa: ritorno troppo alto tReturnFloor: " + dr.tReturnFloor.svalue() );
            needPompa_pp = false;
        }
        if ( dr.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
        {
            dr.LogMessage("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + dr.tInletFloor.svalue() + " > 35" );
            needPompa_pp = false;
        }
        if ( dr.tReturnFireplace < 35 && hour() < 6 ) // fuori oario spengo pompa
        {
            dr.LogMessage("Stop Pompa: orario " + QString::number( hour() ) );
            needPompa_pp = false;
        }
        if ( dr.tReturnFireplace < 35 && hour() >= 11 ) // fuori oario spengo pompa
        {
            dr.LogMessage("Stop Pompa: orario " + QString::number( hour() ) );
            needPompa_pp = false;
        }
        if ( dr.tPufferLow > 55 )   // emergenza
        {
            dr.LogMessage("Emergenza tPufferLow > 55 ");
            needPompa_pp = true;
            needPompa_pt = true;
        }
    }

    dr.LogMessage("needPompa_pt: [" + QString::number(needPompa_pt) + "]" );
    dr.LogMessage("NeedPompa_pp: [" + QString::number(needPompa_pp) + "]" );

    // comandi sulla centrale -----------------------------------------------------
    // accendo pompa pp
    dr.rPompaPianoPrimo.ModifyValue( needPompa_pp );
    //piano terra
    dr.rPompaPianoTerra.ModifyValue( needPompa_pt );
}


/******************************************************************************************************************************************************************/
void  Server::manage_Camino( int sec )
{
    if ( t_Camino.elapsed() < sec * 1000 ) return;
    t_Camino.restart();

    dr.LogMessage("--- Camino ---" );
    bool needPCamino=false;
    bool needPompa_pt=false;

    if (dr.progWinterFIRE)
    {
        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere pompa camino
        dr.LogMessage("Condizione Pompa Camino: tReturnFireplace " + dr.tReturnFireplace.svalue() + " > 34 - " + "tPufferLow " + dr.tPufferLow.svalue() + " > dr.tPufferLow + 5");
        if ( dr.tPufferLow < 45 && dr.tReturnFireplace > 34 && dr.tReturnFireplace > dr.tPufferLow + 5 )
        {
            needPCamino = true;
        }

        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere piano terra
        dr.LogMessage("Condizione dr.tPufferLow > 45 && dr.tReturnFireplace > 45");
        if ( dr.tPufferLow > 45 && dr.tReturnFireplace > 45 )
        {
            needPompa_pt = true;
        }
    }

    dr.LogMessage("NeedPCamino: [" + QString::number(needPCamino) + "]" );
    dr.LogMessage("NeedPompa_pt: [" + QString::number(needPompa_pt) + "]" );

    // heat
    dr.rPompaCamino.ModifyValue( needPCamino );
}
