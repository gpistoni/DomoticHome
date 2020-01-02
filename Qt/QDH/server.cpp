#include "server.h"
#include "../QLibrary/DataTable.h"
#include "../QLibrary/HttpServer.h"
#include "QThread"
#include "QFile"
#include <unistd.h>
#include "effemeridi.h"


// --- CONSTRUCTOR ---
Server::Server(bool runPrograms) :
    dr("192.168.1.200", 80),
    m_runPrograms(runPrograms)
{
    t_UpdateValues.start();
    t_DbLog.start();
    t_BoilerACS.start();
    t_ExternalLight.start();
    t_evRooms.start();
    t_PDC.start();
    t_WinterFIRE.start();
    t_Camino.start();

    t_InternetConnection.start();
    t_Remote212.start();

    m_dbEvents.CreateTables();
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
        dr.LogMessage("VER 1.5.0", true);

        // forced by date
        dr.progBoilerACS.ModifyValue(true);
        dr.progExternalLight.ModifyValue(true);

        if ( winter() )
        {
            dr.progWinterFIRE.ModifyValue(true);
            dr.progWinterPDC_eco.ModifyValue(true);
            dr.progSummerPDC.ModifyValue(false);
            dr.progSummerPDC_eco.ModifyValue(false);
        }
        if ( summer() )
        {
            dr.progWinterFIRE.ModifyValue(false);
            dr.progWinterPDC.ModifyValue(false);
            dr.progWinterPDC_eco.ModifyValue(true);
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

                if ( dr.wCounter > 0  && dr.wSurplus > 0  )
                    dr.wSurplus.m_value = 0;

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
        dr.LogMessage("--- manage_Progs immediate ---"  );
        manage_DbLog(-1);
        manage_ExternalLight(-1);
        manage_BoilerACS(-1);
        manage_Pumps(-1);
        manage_PDC(-1);
        manage_evRooms(-1);

        manage_Internet(-1);
        manage_Remote212(-1);
    }
    else
    {
        manage_DbLog(10*60);
        manage_ExternalLight(10*60);
        manage_BoilerACS(8*60);
        manage_PDC(5*60);
        manage_Pumps(4*60);
        manage_evRooms(10*60);

        manage_Internet(2*60);
        manage_Remote212(2*60);
    }
}

void Server::manage_DbLog(int sec)
{
    if ( t_DbLog.elapsed() < sec * 1000 ) return;
    t_DbLog.restart();
    dr.LogMessage("--- DbLog ---"  );

    m_dbEvents.LogEnergy( dr.wProduced, dr.wConsumed);
}

void Server::manage_Remote212(int sec)
{
    if ( t_Remote212.elapsed() < sec * 1000 ) return;
    t_Remote212.restart();

    dr.LogMessage("--- Remote212 ---"  );

    if (IsNight())                                         // questa si avvia alle 19
    {
        CQHttpClient client2("192.168.1.212", 80, 10000 );
        dr.LogMessage("manage_Remote212 ON");
        client2.Request_Set("on");
    }
    else
    {
        CQHttpClient client2("192.168.1.212", 80, 10000 );
        dr.LogMessage("manage_Remote212 OFF");
        client2.Request_Set("off");
    }
}

void Server::manage_Internet(int sec)
{
    if ( t_InternetConnection.elapsed() < sec * 1000 ) return;
    t_InternetConnection.restart();

    dr.LogMessage("--- RouterInternet ---"  );

    static int decimation = 0;
    if (++decimation%5==0)        // questa parte entra una volta su 5
    {
        QString str;
        bool connected = CQHttpClient::PingGoogle(str);
        dr.LogMessage("Ping Google:");

        if (!connected)
        {
            // off
            CQHttpClient client("192.168.1.210", 80, 10000 );
            dr.LogMessage("manage_Internet OFF/ON"  );
            client.Request_Set("off");
            sleep(10);
        }
    }

    CQHttpClient client2("192.168.1.210", 80, 10000 );
    client2.Request_Set("on");
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
        if ( dr.rBoilerACS && dr.wSurplus > 0 ) // se e gia acceso
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }
        else if ( !dr.rBoilerACS && dr.wSurplus > 400 ) // se e spento
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }

        //decido se accendere il boiler solo a mezzogiorno
        if ( hour() >= 14 && hour() <= 15  )
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON hour:" + QString::number( hour() ) + " >=14 & <17");
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
        if (IsNight() )
        {
            dr.LogMessage("IsNIGHT");
            lightSide = true;
            lightLamp = true;
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
    if (dr.progWinterPDC || dr.progWinterPDC_eco || dr.progWinterFIRE || dr.progSummerPDC || dr.progSummerPDC_eco )
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
            if ( dr.tCameraS > 24 )
            {
                str += " tCamS " + dr.tCameraS.svalue()  + ">" + "24";
                cameraS = true;
            }
            if ( dr.tCameraD >  24  )
            {
                str += " tCamD " + dr.tCameraD.svalue()  + ">" + "24";
                cameraD = true;
                cameraD2 = true;
            }
            if ( dr.tCameraM > 24 )
            {
                str += " tCamM " + dr.tCameraM.svalue()  + ">" + "24";
                cameraM = true;
                cameraM2 = true;
            }
            dr.LogMessage(str);
        }
    }

    //**********************************************************************
    dr.LogMessage("EvRooms s[" +  QString::number(sala) + "] " + " c[" +  QString::number(cucina) + "] " + " cm[" +  QString::number(cameraM) + "] " + " cs[" +  QString::number(cameraS) + "] "+ " cd[" +  QString::number(cameraD) + "] ");

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
    bool needPdc_FullPower = false;
    bool needPdc_Heat = false;

    dr.LogMessage("PDC surplusW:" + dr.wSurplus.svalue() + " [L1]:" + dr.wL1.svalue() + " [L2]:" + dr.wL2.svalue() + " [L3]:" + dr.wL3.svalue());

    float surplus = dr.wSurplus;

    if ( dr.progWinterPDC  || dr.progWinterPDC_eco)
    {
        if (dr.progWinterPDC)
        {
            needPdc = true;
            needPdc_FullPower = false;
        }
        if (dr.progWinterPDC_eco)
        {
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accendere PDC
            if (dr.rPdc && dr.wSurplus>0 )
            {
                dr.LogMessage("PDC ON SurplusW:" + dr.wSurplus.svalue() );
                needPdc = true;
            }
            else if (!dr.rPdc && dr.wSurplus > 500 )
            {
                dr.LogMessage("PDC OFF SurplusW:" + dr.wSurplus.svalue() );
                needPdc = true;
            }

            //pdc Gia Accesa
            if (dr.rPdc && !dr.rPdcFullPower && dr.wSurplus > 300 )
            {    // molto surplus
                dr.LogMessage("PDC FULL POWER SurplusW:" + dr.wSurplus.svalue() );
                needPdc_FullPower = true;
            }
        }

        /**************************************************************************************************/
        if (dr.tExternal > 20 )  // massima t esterna
        {
            dr.LogMessage("PDC OFF t estrerna 20 < " + dr.tExternal.svalue() );
            needPdc = false;
        }

        needPdc_Heat = needPdc;
        needPdc_Pump = needPdc;

        /**************************************************************************************************/
        if ( dr.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
        {
            dr.LogMessage("PDC OFF t inlet " + dr.tInletFloor.svalue() + "> 35" );
            needPdc = false;
        }
    }
    else if (dr.progSummerPDC || dr.progSummerPDC_eco)
    {
        // in estate uso la curva di regolazione termica
        needPdc_FullPower = false;

        if (dr.progSummerPDC)
        {
            needPdc = true;
            needPdc_FullPower = false;
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
                dr.LogMessage("PDC OFF SurplusW:" + dr.wSurplus.svalue() );
                needPdc = true;
            }
        }

        needPdc_Pump = needPdc;
        needPdc_Heat = false;

        /**************************************************************************************************/
        if (needPdc && dr.tInletFloor < 18.5f )  // minima t Acqua raffreddata
        {
            dr.LogMessage("PDC OFF t inlet " + dr.tInletFloor.svalue() + "< 18.5" );
            needPdc = false;
        }
    }

    dr.LogMessage("NeedPdc: [" + QString::number(needPdc) + "]" );
    dr.LogMessage("NeedPdc_FullPower: [" + QString::number(needPdc && needPdc_FullPower) + "]" );
    dr.LogMessage("NeedPdc_Pump [" + QString::number(needPdc_Pump) + "]");
    dr.LogMessage("NeedPdc_Heat [" + QString::number(needPdc && needPdc_Heat) + "]");

    // comandi sulla centrale -----------------------------------------------------
    // accendo PDC
    dr.rPdc.ModifyValue( needPdc );
    // heat
    dr.rPdcHeat.ModifyValue( needPdc && needPdc_Heat );
    //pompa
    dr.rPdcPompa.ModifyValue( needPdc_Pump );
    //night
    dr.rPdcFullPower.ModifyValue( needPdc && needPdc_FullPower );
}

/******************************************************************************************************************************************************************/
void  Server::manage_Pumps( int sec )
{
    if ( t_WinterFIRE.elapsed() < sec * 1000 ) return;
    t_WinterFIRE.restart();

    dr.LogMessage("--- Winter FIRE ---"  );

    bool needPCamino = false;
    bool needPump_pt = false;
    bool needPump_pp = false;

    if (dr.progWinterFIRE || dr.progWinterPDC  || dr.progWinterPDC_eco )
    {
        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere pompa camino
        dr.LogMessage("Condizione Pompa Camino: tReturnFireplace " + dr.tReturnFireplace.svalue() + " > 34 - " + "tPufferLow " + dr.tPufferLow.svalue() + " > dr.tPufferLow + 5");
        if ( hour() >= 23 && dr.tPufferLow < 45 && dr.tReturnFireplace > 34 && dr.tReturnFireplace > dr.tPufferLow + 5 )
        {
            needPCamino = true;
        }
        float tempIn = std::fmax( dr.tInputMixer, std::fmax(dr.tPufferHi, dr.tReturnFireplace) );
        // decido se accendere/spegnere pompa piano primo
        if ( tempIn > 27 && tempIn > dr.tReturnFloor + 4) // ho temperatura
        {
            dr.LogMessage("Condizione Pompa PP insufficiente: tInletFloor: " + dr.tInletFloor.svalue() + " tReturnFloor: " + dr.tReturnFloor.svalue() );
            needPump_pp = true;
        }
        if ( hour() < 6 || hour() >= 23  ) // fuori oario spengo pompa
        {
            dr.LogMessage("Stop Pompa: orario " + QString::number( hour() ) );
            needPump_pp = false;
        }

        if ( (dr.tReturnFloor > 29) )  // ritorno troppo alto - non ne ho bisogno
        {
            dr.LogMessage("Stop Pompa: ritorno troppo alto tReturnFloor: " + dr.tReturnFloor.svalue() );
            needPump_pp = false;
        }
        if ( dr.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
        {
            dr.LogMessage("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + dr.tInletFloor.svalue() + " > 35" );
            needPump_pp = false;
        }

        if (dr.tPufferHi > 35 && hour()>=16 &&  hour()<19 )  // acqua calda in puffer
        {
            needPump_pt = true;  //accendo la pompa
        }
    }

    if (dr.progSummerPDC || dr.progSummerPDC_eco)
    {
        if (dr.tPufferHi < 23 )  // acqua fresca in puffer
        {
            needPump_pp = true;  //accendo la pompa ricircolo
        }
    }

    if (dr.rPdcPompa)
    {
       needPump_pp = true;  //accendo la pompa pp se ho acceso la pdc
    }

    dr.LogMessage("NeedPompa_pt: [" + QString::number(needPump_pt) + "]" );
    dr.LogMessage("NeedPompa_pp: [" + QString::number(needPump_pp) + "]" );

    // comandi sulla centrale -----------------------------------------------------
    // heat
    dr.rPompaCamino.ModifyValue( needPCamino );
    // accendo pompa pp
    dr.rPompaPianoPrimo.ModifyValue( needPump_pp );
    dr.rPompaPianoTerra.ModifyValue( needPump_pt );
}
