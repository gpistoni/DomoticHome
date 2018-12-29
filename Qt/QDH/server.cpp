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

                //dr.LogMessage(" UpdatedValues");
                emit updateValues( &dr );

                ////////////////////////////////////////////////////////////////////////////////////////
                // forced
                dr.progBoilerACS.Value(true);
                dr.progExternalLight.Value(true);

                if (m_runPrograms)
                {
                    manage_ExternalLight(280);
                    manage_BoilerACS(290);
                    manage_Summer(300);
                    manage_Winter(310);
                }
                ////////////////////////////////////////////////////////////////////////////////////////
                //Send Changed
                bool modifiedProg = dr.SendModifiedData();

                if (modifiedProg)
                {
                    manage_BoilerACS(1);
                    manage_ExternalLight(1);
                    manage_Winter(1);
                    manage_Summer(1);
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
        //decido se accendere il boiler sempre se ho un surplus di energia
        if ( dr.wSurplus > ( 500 -  dr.rBoilerACS * 400)  ) // consumo stimato
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
        /**************************************************************************************************/
        dr.LogMessage("darkExternal: " + dr.darkExternal.svalue() + " Request >" + QString::number( 32 - 1 * dr.lampLati )  );
        if ( dr.darkExternal > 32 - 1 * dr.lampLati ) // isteresi
        {
            lightSide = true;
            lightLamp = true;
        }

        /**************************************************************************************************/
        dr.LogMessage("LightLamp [" +  QString::number(lightLamp) + "]  LightSide [" +  QString::number(lightSide) + "]" );
    }

    // attuatori
    dr.lampAngoli.ModifyValue(lightSide);
    dr.lampLati.ModifyValue(lightSide);
    dr.lampPalo.ModifyValue(lightLamp);
    dr.lampExtra.ModifyValue(lightLamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Server::manage_Summer(int sec)
{
    if ( t_Summer.elapsed() < sec * 1000 ) return;
    t_Summer.restart();

    dr.LogMessage("--- Summer ---" + QDateTime::currentDateTime().toString() );

    bool summerAC_pdc  = false;
    bool summerAC_pump = false;
    bool allRoom = false;

    /**************************************************************************************************/
    if (dr.progSummerAC)
    {
        /**************************************************************************************************/
        // decido se accendere le pompe
        if ( dr.tInletFloor  > 20 )  // minima t Acqua raffreddata
        {
            summerAC_pdc = true;
            summerAC_pump = true;
            allRoom = dr.progAllRooms;
        }
        if ( dr.tReturnFloor > 21 )
        {
            summerAC_pump = true;
            allRoom = dr.progAllRooms;
        }

        // spengo pdc se non ho surplus
        if ( dr.progFotoV && ( dr.wSurplus < ( 800 -  dr.rPdc * 700)) ) // surplus < consumostimato
        {
            dr.LogMessage("PDC suspended surplusW:" + dr.wSurplus.svalue() );
            summerAC_pdc = false;
        }

        /**************************************************************************************************/
        dr.LogMessage("summerAC_pdc [" +  QString::number(summerAC_pdc) + "] summerAC_pump [" +   QString::number(summerAC_pump) + "]");
        dr.LogMessage("tInletFloor: " + dr.tInletFloor.svalue() + " tSala: " + dr.tSala.svalue() + " tReturnFloor: " +  dr.tReturnFloor.svalue() );
        dr.LogMessage("tPufferHi: " + dr.tPufferHi.svalue() );
    }

    /**************************************************************************************************/
    // attuatori
    dr.evSala1.ModifyValue(allRoom);
    dr.evSala2.ModifyValue(allRoom);
    dr.evCucina.ModifyValue(allRoom);

    dr.evCameraM1.ModifyValue(summerAC_pump || allRoom);
    dr.evCameraM2.ModifyValue(summerAC_pump || allRoom);
    dr.evCameraS.ModifyValue (summerAC_pump || allRoom);
    dr.evCameraD1.ModifyValue(summerAC_pump || allRoom);
    dr.evCameraD2.ModifyValue(summerAC_pump || allRoom);

    /**************************************************************************************************/
    // accendo PDC
    dr.rPdc.ModifyValue( summerAC_pdc );
    dr.rPdcNightMode.ModifyValue( summerAC_pdc );
    dr.rPdcHeat.ModifyValue( false );
    dr.rPdcPompa.ModifyValue( summerAC_pump );
}

/******************************************************************************************************************************************************************/
void  Server::manage_Winter( int sec )
{
    if ( t_Winter.elapsed() < sec * 1000 ) return;
    t_Winter.restart();

    dr.LogMessage("--- Winter ---" + QDateTime::currentDateTime().toString() );

    bool sala = false;
    bool cucina = false;
    bool cameraS = false;
    bool cameraD = false;
    bool cameraD2 = false;
    bool cameraM = false;
    bool cameraM2 = false;
    bool bagno = false;

    bool needPompa_pt = false;
    bool needPompa_pp = false;
    bool needPdc = false;
    bool needPCamino = false;

    bool allRoom = dr.progAllRooms;

    if (dr.progWinterFIRE || dr.progWinterPDC)
    {
        //////////////////////////////////////////////////////////////////////////////////
        //decido se accendere le stanze
        QString str = "Condizione";
        if ( dr.tSala < dr.tSala.setPoint() )
        {
            str += " tSala " + dr.tSala.svalue()  + " < " + dr.tSala.ssetPoint();
            sala = true;
        }
        if ( dr.tCucina < dr.tCucina.setPoint() )
        {
            str += " tCucina " + dr.tCucina.svalue()  + " < " + dr.tCucina.ssetPoint();
            cucina = true;
        }
        if ( dr.tCameraS < dr.tCameraS.setPoint() )
        {
            str += " tCameraS " + dr.tCameraS.svalue()  + " < " + dr.tCameraS.ssetPoint();
            cameraS = true;
        }
        if ( dr.tCameraD < dr.tCameraD.setPoint() )
        {
            str += " tCameraD " + dr.tCameraD.svalue()  + " < " + dr.tCameraD.ssetPoint();
            cameraD = true;
        }
        if ( dr.tCameraD < dr.tCameraD.setPoint() - 2 )
        {
            cameraD2 = true;
        }
        if ( dr.tCameraM < dr.tCameraM.setPoint() )
        {
            str += " tCameraM " + dr.tCameraM.svalue()  + " < " + dr.tCameraM.ssetPoint();
            cameraM = true;
        }
        if ( dr.tCameraM < dr.tCameraM.setPoint() - 2 )
        {
            cameraM2 = true;
        }
        if ( dr.tBagno < dr.tBagno.setPoint() )
        {
            str += " tBagno " + dr.tBagno.svalue() + " < " + dr.tBagno.ssetPoint();
            bagno = true;
        }
        dr.LogMessage(str);

        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere/spegnere pompa piano primo
        needPompa_pp = ( sala || cucina || bagno || cameraS || cameraD || cameraM );
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
            allRoom = true;
        }
        dr.LogMessage("NeedPompa_pp: [" + QString::number(needPompa_pp) + "]" );

        //////////////////////////////////////////////////////////////////////////////////
        //decido se accendere PDC
        needPdc = dr.progWinterPDC && ( sala || cucina || bagno );

        // spengo pdc se non ho surplus
        if ( dr.progFotoV && ( dr.wSurplus < ( 800 -  dr.rPdc * 700)) ) // surplus < consumostimato
        {
            dr.LogMessage("PDC suspended surplusW:" + dr.wSurplus.svalue() );
            needPdc = false;
        }
        dr.LogMessage("NeedPdc: [" + QString::number(needPdc) + "]" );

        //////////////////////////////////////////////////////////////////////////////////
        // decido se accendere piano terra
        if ( dr.tPufferLow > 45 && dr.tReturnFireplace > 45 )
        {
            dr.LogMessage("Condizione dr.tPufferLow > 45 && dr.tReturnFireplace > 45");
            needPompa_pt = true;
        }
        dr.LogMessage("NeedPompa_pt: [" + QString::number(needPompa_pt) + "]" );

        //////////////////////////////////////////////////////////////////////////////////
        // decido se attivare le elettrovalbole primo piano
        bool NeedEv = false;
        if ( dr.tInletFloor > 25 || needPdc )
        {
            NeedEv = true;
        }
        dr.LogMessage("NeedEv: [" + QString::number(NeedEv) + "]" );

        cameraM   = (cameraM && NeedEv) || allRoom;
        cameraM2  = (cameraM2 && NeedEv);
        sala      = (sala && NeedEv) || allRoom;
        cucina    = (cucina && NeedEv) || allRoom;
        cameraS   = (cameraS && NeedEv) || allRoom;
        cameraD   = (cameraD && NeedEv) || allRoom;
        cameraD2  = (cameraD2 && NeedEv);
    }

    //**********************************************************************
    // elettrovalvole stanze -----------------------------------------------------------------------
    dr.evCameraM1.ModifyValue(cameraM);
    dr.evCameraM2.ModifyValue(cameraM2);
    dr.evSala1.ModifyValue(sala);
    dr.evSala2.ModifyValue(sala);
    dr.evCucina.ModifyValue(cucina);
    dr.evCameraS.ModifyValue(cameraS);
    dr.evCameraD1.ModifyValue(cameraD);
    dr.evCameraD2.ModifyValue(cameraD2);

    // comandi semimanuali centrale -----------------------------------------------------
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
    dr.rPdcNightMode.ModifyValue( needPdc );
    //camino
    dr.rPompaCamino.ModifyValue( needPCamino );
}

