#include "server.h"
#include "../QLibrary/DataTable.h"
#include "../QLibrary/HttpServer.h"
#include "../QLibrary/HttpServer2.h"
#include "QThread"
#include "QFile"
//#include <unistd.h>
#include "effemeridi.h"


// --- CONSTRUCTOR ---
ServerDH::ServerDH(bool runPrograms ) :
    dr("192.168.1.200", 80),
    m_runPrograms(runPrograms)
{
    t_DbLog.start();
    t_PushWebData.start();
    t_BoilerACS.start();
    t_ExternalLight.start();
    t_evRooms.start();
    t_PDC.start();
    t_WinterFIRE.start();
    t_Camino.start();

    t_InternetConnection.start();
    t_Remote212.start();
    t_Remote216.start();

    //m_dbEvents.CreateTables();
}

// --- DECONSTRUCTOR ---
ServerDH::~ServerDH() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void ServerDH::run()
{
    //HttpServer.startServer(&dr);

    m_DbManager.Init(&dr);

    while (m_running)
    {
        dr.LogMessage(SERVER_VER,true);

        // force always
        dr.progBoilerACS.ModifyValue(true);
        dr.progExternalLight.ModifyValue(true);

        // forced by date
        if ( winter() )
        {
            dr.LogMessage("WINTER");
            dr.progWinterFIRE.ModifyValue(true);
            dr.progWinterPDC_eco.ModifyValue(true);
            //------------------------------
            dr.progSummerPDC.ModifyValue(false);
            dr.progSummerPDC_eco.ModifyValue(false);
        }
        if ( summer() )
        {
            dr.LogMessage("SUMMER");
            dr.progWinterFIRE.ModifyValue(false);
            dr.progWinterPDC.ModifyValue(false);
            dr.progWinterPDC_eco.ModifyValue(false);
            //------------------------------
            dr.progSummerPDC_eco.ModifyValue(true);
        }

        int firstrun =1;
        try {
            while (m_running)
            {
                QThread::msleep(1000);  //milliseconds

                /////////////////////////////////////////////////////////////////////////////////////////
                dr.ReadData();

                dr.wProduced.m_value *= 1.15f;

                // calcoli
                dr.wConsumed += dr.wL1;
                dr.wConsumed += dr.wL2;
                dr.wConsumed += dr.wL3;

                dr.wSurplus = dr.wProduced;
                dr.wSurplus -= dr.wConsumed;

                if (dr.wConsumed<dr.wProduced) dr.wSelfConsumed = dr.wConsumed;
                if (dr.wProduced<dr.wConsumed) dr.wSelfConsumed = dr.wProduced;

                dr.LogPoint();
                emit updateValues( &dr );

                ////////////////////////////////////////////////////////////////////////////////////////
                if (m_runPrograms)
                {
                    manage_Progs(false);
                }

                ////////////////////////////////////////////////////////////////////////////////////////
                //Send Changed
                bool modifiedProg = dr.SendModifiedData();
                if (modifiedProg || firstrun)
                {
                    manage_Progs(true);
                    firstrun =0;
                }
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

void ServerDH::manage_Progs(bool immediate)
{
    if (immediate)
    {
        dr.LogMessage("--- Manage_Progs immediate ---"  );
        manage_DbLog(-1);

        manage_ExternalLight(-1);
        manage_BoilerACS(-1);
        manage_Pumps(-1);
        manage_PDC(-1);
        manage_EvRooms(-1);

        manage_Remote210_Internet(-1);
        manage_Remote212_Freezer(-1);
        manage_Remote216_Christmas(-1);
    }
    else
    {
        manage_DbLog(10*60);
        manage_PushWebData(15*60);

        manage_ExternalLight(5*60);
        manage_BoilerACS(9*60);
        manage_PDC(5*60);
        manage_Pumps(3*60);
        manage_EvRooms(10*60);

        manage_Remote210_Internet(3*60);        //Remote bug - 5 minute max pool time
        manage_Remote212_Freezer(5*60);
        manage_Remote216_Christmas(5*60);
    }
}

void ServerDH::manage_PushWebData(int sec)
{
    if (!t_PushWebData.hasExpired(sec * 1000)) return;
    t_PushWebData.restart();
    dr.LogMessage("--- PushWebData ---"  );

    m_DbManager.LogEnergy();
}


void ServerDH::manage_DbLog(int sec)
{
    if (!t_DbLog.hasExpired(sec * 1000) ) return;
    t_DbLog.restart();

    //dr.LogMessage("--- DbLog ---"  );
    //m_dbEvents.LogEnergy( (int)dr.wProduced, (int)dr.wConsumed, (int)dr.wL1, (int)dr.wL2, (int)dr.wL3);
    //m_dbEvents.LogTemperature( dr );
}

void ServerDH::manage_Remote212_Freezer(int sec)
{
    if ( t_Remote212.elapsed() < sec * 1000 ) return;
    t_Remote212.restart();

    dr.LogMessage("--- Remote212_Freezer ---"  );

    //bool setOn = dr.wSurplus > 300;   // questa si avvia con suplus oppure dalle 8 alle 24
    //setOn |= Is8_24Day();

    bool setOn = (IsNight() && hour()>17 && hour()<23);              // Freezer->Natale
    setOn |= (IsNight() && day()==25 && month()==12);

    if (setOn)
    {
        CQHttpClient client2("192.168.1.212", 80, 10000 );
        dr.LogMessage("manage_Remote212 [1]");
        client2.Request("on");
    }
    else
    {
        CQHttpClient client2("192.168.1.212", 80, 10000 );
        dr.LogMessage("manage_Remote212 [0]");
        client2.Request("off");
    }
}

void ServerDH::manage_Remote216_Christmas(int sec)
{
    if ( t_Remote216.elapsed() < sec * 1000 ) return;
    t_Remote216.restart();

    dr.LogMessage("--- Remote216_Christmas ---"  );

    if ( (IsNight() && hour()>17) || (IsNight() && day()==25 && month()==12) )
    {
        dr.LogMessage(QString("IsNight && Hour:") +  hour() +  ">17");
        CQHttpClient client2("192.168.1.216", 80, 10000 );
        dr.LogMessage("manage_Remote216 [1]");
        client2.Request("on");
    }
    else
    {
        CQHttpClient client2("192.168.1.216", 80, 10000 );
        dr.LogMessage("manage_Remote216 [0]");
        client2.Request("off");
    }
}

void ServerDH::manage_Remote210_Internet(int sec)
{
    if ( t_InternetConnection.elapsed() < sec * 1000 ) return;
    t_InternetConnection.restart();

    // watchdog
    emit tickWatchdog();

    /*
    if ( hour() >=2 && hour()< 8 )
    {
        CQHttpClient client1("192.168.1.210", 80, 10000 );
        client1.Request("off");
        dr.LogEvent("Network DISABLED");
        return;
    }
    */

    dr.LogMessage("--- RouterInternet ---"  );
    QString str;
    int ttt=0;
    bool connected = CQHttpClient::PingGoogle(str); ttt++;
    if (!connected)
    {
        dr.LogMessage("Ping Google failed");
        QThread::sleep(5);
        bool connected2 = CQHttpClient::PingGoogle(str); ttt++;
        if (!connected2)
        {
            dr.LogMessage("Ping Google failed");
            QThread::sleep(5);
            bool connected3 = CQHttpClient::PingGoogle(str); ttt++;
            if (!connected3)
            {
                dr.LogEvent("Network RESTART");
                dr.LogMessage("Ping Google failed: RESTART");
                // Off
                CQHttpClient client21("192.168.1.210", 80, 10000 );
                client21.Request("off");
                QThread::sleep(5);
                CQHttpClient client22("192.168.1.210", 80, 10000 );
                client22.Request("on");
                QThread::sleep(1);
                client22.Request("on");
                t_InternetConnection.restart();     // rivvio il conteggio
                return;
            }
        }
    }

    //dr.LogEvent("Network OK [" + QString::number( ttt ) + "]");
    t_InternetConnection.restart();                    //   rivvio il conteggio
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerDH::manage_BoilerACS(int sec)
{
    if ( t_BoilerACS.elapsed() < sec * 1000 ) return;
    t_BoilerACS.restart();

    dr.LogMessage("--- BoilerACS ---"  );

    bool boilerACS = false;
    /**************************************************************************************************/
    if ( dr.progBoilerACS )
    {
        if ( dr.rBoilerACS && dr.wSurplus > 200 ) // se e gia acceso
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }
        else if ( !dr.rBoilerACS && dr.wSurplus > 600 ) // se e spento
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
        }

        //decido se accendere il boiler versomezzogiorno
        if ( hour() >= 13 && hour() <= 14 )
        {
            boilerACS = true;
            dr.LogMessage("Condizione ON hour:" + QString::number( hour() ) + " >=13&<14");
        }
    }
    /**************************************************************************************************/
    // boiler
    dr.LogMessage("BoilerACS [" + QString::number( boilerACS ) + "]");
    dr.rBoilerACS.ModifyValue( boilerACS );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerDH::manage_ExternalLight(int sec)
{
    if ( t_ExternalLight.elapsed() < sec * 1000 ) return;
    t_ExternalLight.restart();

    dr.LogMessage("--- ExternalLight ---"  );
    dr.LogMessage(QDateTime::currentDateTime().date().toString() );

    bool lightSide = false;
    bool lightLamp = false;

    if (dr.progExternalLight)
    {
        if (IsNight())
        {
            dr.LogMessage("IsNIGHT");
            lightSide = true;
            lightLamp = true;
        }
        int hour = QDateTime::currentDateTime().time().hour();
        if (hour<12)
            lightLamp = false;
    }

    dr.LogMessage("LightLamp [" +  QString::number(lightLamp) + "] " );
    dr.LogMessage("LightSide [" +  QString::number(lightSide) + "]" );

    // attuatori
    dr.lampAngoli.SetValue(lightSide);
    dr.lampLati.SetValue(lightSide);
    dr.lampPalo.SetValue(lightLamp);
    dr.lampExtra.SetValue(lightLamp);

    QString Request = "http://192.168.1.21/?";
    Request += "L1=" + QString::number(lightSide);
    Request += "&L2=" + QString::number(lightSide);
    Request += "&L3=" + QString::number(lightLamp);
    Request += "&L4=" + QString::number(lightLamp);
    Request += "&L5=0";
    Request += "&L6=0";
    Request += "&L7=0";
    Request += "&L8=0";

    HttpRequest request;
    QString result = request.executeBlockingGet(Request);

    dr.LogMessage(Request);
    dr.LogMessage(result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  ServerDH::manage_EvRooms( int sec )
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
    if (dr.progWinterPDC || dr.progWinterPDC_eco || dr.progWinterFIRE )
    {
        if ( (hour() >= 6 ) && (dr.rPompaPianoPrimo || dr.rPompaPianoTerra || dr.rPdcPompa || dr.tInputMixer > 28) )
        {
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accendere le stanze
            QString str = "Stanze:";
            if ( dr.tSala < dr.tSala.setPoint() )
            {
                str += " tSal " + dr.tSala.svalue()  + "<" + dr.tSala.ssetPoint();
                sala = true;
            }
            if ( dr.tSala < dr.tSala.setPoint(-1) )
            {
                str += " tSal2 " + dr.tSala.svalue()  + "<" + dr.tSala.ssetPoint();
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
            if ( dr.tSala > 25  )
            {
                str += " tSala " + dr.tSala.svalue()   + ">" + "25";
                sala = true;
                sala2 = true;
            }
            if ( dr.tCucina > 25  )
            {
                str += " tCuc " + dr.tCucina.svalue()  + ">" + "25";
                cucina = true;
            }
            if ( dr.tCameraS > 23 )
            {
                str += " tCamS " + dr.tCameraS.svalue()  + ">" + "23";
                cameraS = true;
            }
            if ( dr.tCameraD >  23 )
            {
                str += " tCamD " + dr.tCameraD.svalue()  + ">" + "23";
                cameraD = true;
                cameraD2 = true;
            }
            if ( dr.tCameraM > 23 )
            {
                str += " tCamM " + dr.tCameraM.svalue()  + ">" + "23";
                cameraM = true;
                cameraM2 = true;
            }
            dr.LogMessage(str);
        }
    }

    //**********************************************************************
    dr.LogMessage("EvRooms sa[" +  QString::number(sala) + "]"
                  + " cu[" +  QString::number(cucina) + "]"
                  + " cm[" +  QString::number(cameraM) + "]"
                  + " cs[" +  QString::number(cameraS) + "]"
                  + " cd[" +  QString::number(cameraD) + "]");

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
void  ServerDH::manage_PDC( int sec )
{
    if ( t_PDC.elapsed() < sec * 1000 ) return;
    t_PDC.restart();

    dr.LogMessage("--- PDC ---" );

    bool needPdc = false;
    bool needPdc_Pump = false;
    bool needPdc_FullPower = false;
    bool needPdc_Heat = false;

    dr.LogMessage("Surplus:" + dr.wSurplus.svalue() + " L1:" + dr.wL1.svalue() + " L2:" + dr.wL2.svalue() + " L3:" + dr.wL3.svalue());

    if ( dr.progWinterPDC  || dr.progWinterPDC_eco)
    {
        if (dr.progWinterPDC)
        {
            dr.LogMessage("PDC ON progWinterPDC" );
            needPdc = true;
            needPdc_FullPower = false;
        }
        else if (dr.progWinterPDC_eco)
        {
            // se BoilerACS non e' gia attivo
            if (!dr.rBoilerACS )
            {
                manage_BoilerACS(3);
            }
            else
            {
                //////////////////////////////////////////////////////////////////////////////////
                //decido se accendere PDC
                if (!dr.rPdcNightMode)
                {
                    if ( (dr.rPdc && dr.wSurplus > 300) ||
                            (!dr.rPdc && dr.wSurplus > 1000))
                    {
                        dr.LogMessage("PDC ON progWinterPDC_eco SurplusW" + dr.wSurplus.svalue() );
                        needPdc = true;
                    }
                }
                //////////////////////////////////////////////////////////////////////////////////
                //decido se accender FULL POWER
                //pdc Gia Accesa
                if (dr.rPdc)
                {
                    if( (!dr.rPdcNightMode && dr.wSurplus > 300) ||
                            (dr.rPdcNightMode && dr.wSurplus > 1000) )
                    {    // molto surplus
                        dr.LogMessage("PDC FULL POWER progWinterPDC_eco SurplusW" + dr.wSurplus.svalue() );
                        needPdc_FullPower = true;
                    }
                }
                //////////////////////////////////////////////////////////////////////////////////
            }
        }

        /**************************************************************************************************/
        if (dr.tExternal > 20 )  // massima t esterna
        {
            dr.LogMessage("PDC OFF tEsterna" + dr.tExternal.svalue() + " >20" );
            needPdc = false;
        }

        needPdc_Pump = needPdc;
        needPdc_Heat = true;

        /**************************************************************************************************/
        if ( dr.tInletFloor > 37 )  // 35 è la sicurezza dopo la quale spengo la pompa
        {
            dr.LogMessage("PDC OFF tInlet" + dr.tInletFloor.svalue() + "> 37" );
            needPdc = false;
        }
    }
    else if (dr.progSummerPDC || dr.progSummerPDC_eco)
    {
        needPdc_FullPower = false;

        if (dr.progSummerPDC)
        {
            dr.LogMessage("PDC ON progSummerPDC" );
            needPdc = true;
            needPdc_FullPower = false;
        }
        if (dr.progSummerPDC_eco)
        {
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accendere PDC
            if ((!dr.rPdcNightMode) ||
                    (dr.rPdc &&  dr.wSurplus  > 300) ||
                    (!dr.rPdc &&  dr.wSurplus  > 1000))
            {
                dr.LogMessage("PDC ON progSummerPDC_eco SurplusW" + dr.wSurplus.svalue() );
                needPdc = true;
            }
            //////////////////////////////////////////////////////////////////////////////////
            //decido se accender FULL POWER
            //pdc Gia Accesa
            if (dr.rPdc && dr.rBoilerACS)
            {
                if( (!dr.rPdcNightMode && dr.wSurplus > 300) ||
                        (dr.rPdcNightMode && dr.wSurplus > 1000) )
                {    // molto surplus
                    dr.LogMessage("PDC FULL POWER progSummerPDC_eco SurplusW" + dr.wSurplus.svalue() );
                    needPdc_FullPower = true;
                }
            }
            //////////////////////////////////////////////////////////////////////////////////
            needPdc_Pump = needPdc;
            needPdc_Heat = false;

            /**************************************************************************************************/
            if (dr.tInletFloor < 18.f )  // minima t Acqua raffreddata
            {
                dr.LogMessage("PDC OFF tInletFloor" + dr.tInletFloor.svalue() + "< 18" );
                needPdc = false;
            }

            if ( dr.tPufferHi < 18.f)   // minima t Acqua raffreddata
            {
                dr.LogMessage("PDC OFF tPufferHi" + dr.tPufferHi.svalue() + "< 18" );
                needPdc = false;
            }

            /**************************************************************************************************/
            if (dr.tExternal < 23 )  // minima t esterna
            {
                dr.LogMessage("PDC OFF tEsterna" + dr.tExternal.svalue() + " <23" );
                needPdc = false;
            }
        }
    }

    dr.LogMessage("Pdc:[" + QString::number(needPdc) + "] " +
                  + "NightMode:[" + QString::number(needPdc && !needPdc_FullPower) + "] "+
                  + "Pump:[" + QString::number(needPdc_Pump) + "] " +
                  + "Heat:[" + QString::number(needPdc_Heat) + "] ");

    // comandi sulla centrale -----------------------------------------------------
    // accendo PDC
    dr.rPdc.ModifyValue( needPdc );
    // heat
    dr.rPdcHeat.ModifyValue( needPdc_Heat );
    //pompa
    dr.rPdcPompa.ModifyValue( needPdc_Pump );
    //night
    dr.rPdcNightMode.ModifyValue( needPdc && !needPdc_FullPower );

}

/******************************************************************************************************************************************************************/
void  ServerDH::manage_Pumps( int sec )
{
    if ( t_WinterFIRE.elapsed() < sec * 1000 ) return;
    t_WinterFIRE.restart();

    dr.LogMessage("--- Manage PUMPS ---"  );

    bool needPCamino = false;
    bool needPump_pt = false;
    bool needPump_pp = false;

    dr.LogMessage("Temps pLOW:" + dr.tPufferLow.svalue() + " pHI:" +  dr.tPufferHi.svalue()  + " Inlet:" + dr.tInletFloor.svalue() + " Return:" + dr.tReturnFloor.svalue() );

    if (dr.progWinterFIRE || dr.progWinterPDC  || dr.progWinterPDC_eco )
    {
        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere pompa camino
//        if (dr.tReturnFireplace > 35 && dr.tReturnFireplace > dr.tPufferLow + 5 )
//       {
//            dr.LogMessage("Condizione Pompa Camino: tReturnFireplace" + dr.tReturnFireplace.svalue() + " > 35 && tReturnFireplace" + dr.tReturnFireplace.svalue() + " > " + "tPufferLow" + dr.tPufferLow.svalue() + " + 5");
//           needPCamino = true;
//        }
        /////////////////////////////////////////////////////////////////////////////////////
        float tempIn = std::max( dr.tInputMixer.m_value, std::max(dr.tPufferHi.m_value, dr.tReturnFireplace.m_value) );
        // decido se accendere/spegnere pompa piano primo
        if ( tempIn > 27 && tempIn > dr.tReturnFloor + 4) // ho temperatura
        {
            dr.LogMessage("Condizione Pompa PP ON: " + QString::number( tempIn ) + "> 25  && >tRet: " + dr.tReturnFloor.svalue() );
            needPump_pp = true;
        }
        if (dr.rPdc)    // se va la pdc deve andare la pompa necessariamente
        {
            dr.LogMessage("Condizione Pompa PP ON: Pdc On");
            needPump_pp = true;
        }
        if (dr.tPufferHi > 40 && hour()>=16 &&  hour()<19 )  // acqua calda in puffer
        {
            dr.LogMessage("Condizione Pompa PT ON: tPufferHi: " + dr.tPufferHi.svalue() );
            needPump_pt = true;  //accendo la pompa piano terra
        }
        /////////////////////////////////////////////////////////////////////////////////////
        if ( hour() < 6 || hour() >= 23  ) // fuori oario spengo pompa
        {
            dr.LogMessage("Stop Pompa: orario " + QString::number( hour() ) );
            needPump_pp = false;
        }
        if ( (dr.tReturnFloor > 30) && !(dr.rPdc) )  // ritorno troppo alto - non ne ho bisogno
        {
            dr.LogMessage("Stop Pompa: ritorno troppo alto tReturnFloor: " + dr.tReturnFloor.svalue() );
            needPump_pp = false;
        }
        if ( dr.tInletFloor > 35 )  // 36 è la sicurezza dopo al quale spengo la pompa
        {
            dr.LogMessage("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + dr.tInletFloor.svalue() + " > 35" );
            needPump_pp = false;
        }
    }

    if (dr.progSummerPDC || dr.progSummerPDC_eco)
    {
        if (dr.tPufferLow < 23 && !IsNight()  )  // acqua fresca in puffer
        {
            needPump_pp = true;  //accendo la pompa ricircolo
        }
    }

    dr.LogMessage("Pompa_pt:[" + QString::number(needPump_pt) +  "]" +
                  " Pompa_pp:[" + QString::number(needPump_pp) + "]" +
                  " Pompa_ca:[" + QString::number(needPCamino) + "]" );

    // comandi sulla centrale -----------------------------------------------------
    // heat
    dr.rPompaCamino.ModifyValue( needPCamino );
    // accendo pompa pp
    dr.rPompaPianoPrimo.ModifyValue( needPump_pp );
    dr.rPompaPianoTerra.ModifyValue( needPump_pt );
}
