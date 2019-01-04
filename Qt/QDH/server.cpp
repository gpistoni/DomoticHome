#include "server.h"
#include "../QLibrary/DataTable.h"
#include "QThread"
#include "QFile"


// --- CONSTRUCTOR ---
Server::Server(bool runPrograms) :
    dr("192.168.1.200", 80),
    m_runPrograms(runPrograms)
{
    t_UpdateValues.start();
    t_BoilerACS.start();
    t_ExternalLight.start();
    t_evRooms.start();
    t_Winter.start();
    t_Summer.start();
}

// --- DECONSTRUCTOR ---
Server::~Server() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Server::run()
{
    bool firstRun = true;
    while (m_running)
    {
        dr.LogMessage("VER 1.0.8", true);

        try {
            while (m_running)
            {
                QThread::msleep(1);  //milliseconds

                if ( t_UpdateValues.elapsed() < 1000 )
                    continue;
                t_UpdateValues.restart();

                /////////////////////////////////////////////////////////////////////////////////////////
                dr.ReadData();

                ////////////////////////////////////////////////////////////////////////////////////////
                // forced by date
                dr.progBoilerACS.Value(true);
                dr.progExternalLight.Value(true);
                dr.progFotoV.Value(true);

                if ( winter() )
                {
                    dr.progWinterFIRE.Value(true);
                    dr.progSummerAC.Value(false);
                }
                if ( summer() )
                {
                    dr.progWinterFIRE.Value(false);
                    dr.progSummerAC.Value(true);
                }
                ////////////////////////////////////////////////////////////////////////////////////////
                // calcoli
                dr.wConsumed += dr.wL1;
                dr.wConsumed += dr.wL2;
                dr.wConsumed += dr.wL3;
                dr.wSurplus += dr.wProduced;
                dr.wSurplus -= dr.wConsumed;

                dr.LogPoint();
                emit updateValues( &dr );

                ////////////////////////////////////////////////////////////////////////////////////////
                if (m_runPrograms)
                {
                    if (firstRun) manage_Progs(true);
                    else          manage_Progs(false);
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
        manage_ExternalLight(1);
        manage_BoilerACS(1);
        manage_Summer(1);
        manage_Winter(1);
        manage_evRooms(1);
    }
    else
    {
        manage_ExternalLight(120);
        manage_BoilerACS(250);
        manage_Winter(400);
        manage_Summer(410);
        manage_evRooms(500);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_BoilerACS(int sec)
{
    if ( t_BoilerACS.elapsed() < sec * 1000 )
        return;
    t_BoilerACS.restart();

    dr.LogMessage("--- BoilerACS ---"  + QDateTime::currentDateTime().toString() );

    bool boilerACS = false;
    /**************************************************************************************************/
    if ( dr.progBoilerACS )
    {
        if ( dr.rBoilerACS )
        {
            if ( dr.wSurplus > 100)
            {
                boilerACS = true;
                dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
            }
        }
        else
        {
            if ( dr.wSurplus > 500)
            {
                boilerACS = true;
                dr.LogMessage("Condizione ON surplusW:" + dr.wSurplus.svalue() );
            }
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
            dr.LogMessage("Condizione OFF dr.ReturnFireplace:" + dr.tReturnFireplace.svalue() + "> 30");
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
    if ( t_ExternalLight.elapsed() < sec * 1000 )
        return;
    t_ExternalLight.restart();

    dr.LogMessage("--- ExternalLight ---" + QDateTime::currentDateTime().toString() );

    bool lightSide = false;
    bool lightLamp = false;

    if (dr.progExternalLight)
    {
        if ( hour()>=18 || hour() <=7)
        {
            /**************************************************************************************************/
            dr.LogMessage("darkExternal: " + dr.darkExternal.svalue() + " Request >" + QString::number( 32 - 2 * dr.lampLati )  );
            if ( dr.darkExternal > (32 - 2 * dr.lampLati) ) // isteresi
            {
                lightSide = true;
                lightLamp = true;
            }

            if ( hour() < 7 )
                lightLamp = false;

        }
        dr.LogMessage("LightLamp [" +  QString::number(lightLamp) + "] " );
        dr.LogMessage("LightSide [" +  QString::number(lightSide) + "]" );
    }

    // attuatori
    dr.lampAngoli.ModifyValue(lightSide);
    dr.lampLati.ModifyValue(lightSide);
    dr.lampPalo.ModifyValue(lightLamp);
    dr.lampExtra.ModifyValue(lightLamp);
}

void  Server::manage_evRooms( int sec )
{
    if ( t_evRooms.elapsed() < sec * 1000 ) return;
    t_evRooms.restart();

    dr.LogMessage("--- EvRooms ---" + QDateTime::currentDateTime().toString() );

    bool sala = false;
    bool cucina = false;
    bool cameraS = false;
    bool cameraD = false;
    bool cameraD2 = false;
    bool cameraM = false;
    bool cameraM2 = false;

    bool allRoom = dr.progAllRooms;

    if (dr.rPompaPianoPrimo || dr.rPompaPianoTerra || dr.rPdcPompa || dr.tInputMixer > 30)
    {
        //////////////////////////////////////////////////////////////////////////////////
        //decido se accendere le stanze
        QString str = "Stanze";
        if ( dr.tSala < dr.tSala.setPoint() )
        {
            str += "\ntSala " + dr.tSala.svalue()  + " < " + dr.tSala.ssetPoint();
            sala = true;
        }
        if ( dr.tCucina < dr.tCucina.setPoint() )
        {
            str += "\ntCucina " + dr.tCucina.svalue()  + " < " + dr.tCucina.ssetPoint();
            cucina = true;
        }
        if ( dr.tCameraS < dr.tCameraS.setPoint() )
        {
            str += "\ntCameraS " + dr.tCameraS.svalue()  + " < " + dr.tCameraS.ssetPoint();
            cameraS = true;
        }
        if ( dr.tCameraD < dr.tCameraD.setPoint() )
        {
            str += "\ntCameraD " + dr.tCameraD.svalue()  + " < " + dr.tCameraD.ssetPoint();
            cameraD = true;
        }
        if ( dr.tCameraD < dr.tCameraD.setPoint() - 2 )
        {
            cameraD2 = true;
        }
        if ( dr.tCameraM < dr.tCameraM.setPoint() )
        {
            str += "\ntCameraM " + dr.tCameraM.svalue()  + " < " + dr.tCameraM.ssetPoint();
            cameraM = true;
        }
        if ( dr.tCameraM < dr.tCameraM.setPoint() - 2 )
        {
            cameraM2 = true;
        }
        dr.LogMessage(str);
    }

    //**********************************************************************
    // elettrovalvole stanze -----------------------------------------------------------------------
    dr.evCameraM1.ModifyValue(cameraM || allRoom);
    dr.evCameraM2.ModifyValue(cameraM2 || allRoom);
    dr.evSala1.ModifyValue(sala || allRoom);
    dr.evSala2.ModifyValue(sala || allRoom );
    dr.evCucina.ModifyValue(cucina || allRoom );
    dr.evCameraS.ModifyValue(cameraS || allRoom );
    dr.evCameraD1.ModifyValue(cameraD || allRoom );
    dr.evCameraD2.ModifyValue(cameraD2 || allRoom);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_Summer(int sec)
{
    if ( t_Summer.elapsed() < sec * 1000 ) return;
    t_Summer.restart();

    dr.LogMessage("--- Summer ---" + QDateTime::currentDateTime().toString() );

    bool needPdc  = false;
    bool needPdc_Pump = false;
    bool needPdc_Night = true;
    bool allRoom = false;

    /**************************************************************************************************/
    if (dr.progSummerAC)
    {
        allRoom = dr.progAllRooms;
        /**************************************************************************************************/
        // decido se accendere le pompe
        if ( dr.tInletFloor  > 20 )  // minima t Acqua raffreddata
        {
            needPdc = true;
            needPdc_Pump = true;

        }
        else if ( dr.tInletFloor  < 25 )
        {
            needPdc_Pump = true;
            allRoom = dr.progAllRooms;
        }

        if ( dr.progFotoV  )
        {
            dr.LogMessage("PDC surplusW:" + dr.wSurplus.svalue() );

            if (dr.rPdc)
            {   //pdc Gia Accesa
                if ( dr.wSurplus >500 )
                {    // molto surplus
                    dr.LogMessage("PDC Molto SurplusW:" + dr.wSurplus.svalue() );
                    needPdc_Night = false;
                }
                if ( dr.wSurplus < 200 )
                {
                    dr.LogMessage("PDC Insufficiente SurplusW:" + dr.wSurplus.svalue() );
                    needPdc =false;
                }
            }
            else
            {   //pdc Spenta
                if ( dr.wSurplus < 700 )
                {
                    dr.LogMessage("PDC Insufficiente SurplusW:" + dr.wSurplus.svalue() );
                    needPdc =false;
                }
            }
        }

        /**************************************************************************************************/
        dr.LogMessage("summerAC_pdc [" +  QString::number(needPdc) + "]");
        dr.LogMessage("summerAC_pump [" +   QString::number(needPdc_Pump) + "]");
        dr.LogMessage("summerAC_night [" +   QString::number(needPdc_Night) + "]");

        dr.LogMessage("tInletFloor: " + dr.tInletFloor.svalue() + " tSala: " + dr.tSala.svalue() + " tReturnFloor: " +  dr.tReturnFloor.svalue() );
        dr.LogMessage("tPufferHi: " + dr.tPufferHi.svalue() );
    }

    /**************************************************************************************************/
    // attuatori
    dr.evSala1.ModifyValue(allRoom);
    dr.evSala2.ModifyValue(allRoom);
    dr.evCucina.ModifyValue(allRoom);

    dr.evCameraM1.ModifyValue(needPdc || allRoom);
    dr.evCameraM2.ModifyValue(needPdc || allRoom);
    dr.evCameraS.ModifyValue (needPdc || allRoom);
    dr.evCameraD1.ModifyValue(needPdc || allRoom);
    dr.evCameraD2.ModifyValue(needPdc || allRoom);

    /**************************************************************************************************/
    // accendo PDC
    dr.rPdc.ModifyValue( needPdc );
    dr.rPdcNightMode.ModifyValue( needPdc && needPdc_Night );
    dr.rPdcHeat.ModifyValue( false );
    dr.rPdcPompa.ModifyValue( needPdc_Pump );
}


/******************************************************************************************************************************************************************/
void  Server::manage_Winter( int sec )
{
    if ( t_Winter.elapsed() < sec * 1000 ) return;
    t_Winter.restart();

    dr.LogMessage("--- Winter ---" + QDateTime::currentDateTime().toString() );

    bool needPompa_Camino = false;
    bool needPompa_pt = false;
    bool needPompa_pp = false;
    bool needPdc = false;
    bool needPdc_Night = true;

    if (dr.progWinterFIRE || dr.progWinterPDC)
    {
        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere/spegnere pompa piano primo
        needPompa_pp = true;
        if ( dr.tInputMixer < 28 && dr.tPufferHi < 28 && dr.tReturnFireplace < 28 )   // non ho temperatura
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
        if ( dr.tReturnFireplace < 35 && hour() < 5 ) // fuori oario
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


        //////////////////////////////////////////////////////////////////////////////////
        //decido se accendere PDC
        needPdc = dr.progWinterPDC && !needPompa_pp;

        if ( dr.progFotoV  )
        {
            dr.LogMessage("PDC surplusW:" + dr.wSurplus.svalue() );

            if (dr.rPdc)
            {   //pdc Gia Accesa
                if ( dr.wSurplus >500 )
                {    // molto surplus
                    dr.LogMessage("PDC Molto SurplusW:" + dr.wSurplus.svalue() );
                    needPdc_Night = false;
                    needPompa_pp = true;
                    needPompa_pt = true;
                }
                if ( dr.wSurplus < 200 )
                {
                    dr.LogMessage("PDC Insufficiente SurplusW:" + dr.wSurplus.svalue() );
                    needPdc =false;
                }
            }
            else
            {   //pdc Spenta
                if ( dr.wSurplus < 700 )
                {
                    dr.LogMessage("PDC Insufficiente SurplusW:" + dr.wSurplus.svalue() );
                    needPdc =false;
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere piano terra
        if ( dr.tPufferLow > 45 && dr.tReturnFireplace > 45 )
        {
            dr.LogMessage("Condizione dr.tPufferLow > 45 && dr.tReturnFireplace > 45");
            needPompa_pt = true;
        }

        dr.LogMessage("NeedPdc: [" + QString::number(needPdc) + "]" );
        dr.LogMessage("NeedPompa_pp: [" + QString::number(needPompa_pp) + "]" );
        dr.LogMessage("NeedPompa_pt: [" + QString::number(needPompa_pt) + "]" );
        dr.LogMessage("NeedPompa_camino: [" + QString::number(needPompa_Camino) + "]" );
    }

    // comandi sulla centrale -----------------------------------------------------
    // accendo pompa pp
    dr.rPompaPianoPrimo.ModifyValue( needPompa_pp );
    //piano terra
    dr.rPompaPianoTerra.ModifyValue( needPompa_pt );
    // accendo PDC
    dr.rPdc.ModifyValue( needPdc );
    // heat
    dr.rPdcHeat.ModifyValue( needPdc );
    //pompa
    dr.rPdcPompa.ModifyValue( needPdc );
    //night
    dr.rPdcNightMode.ModifyValue( needPdc && needPdc_Night );
    //camino
    dr.rPompaCamino.ModifyValue( needPompa_Camino );
}

