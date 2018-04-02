#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Time.h>

#include "dhwifi.h"
#include "dhconfig.h"
#include "DataTable.h"
#include "functions.h"
#include "httpServer2.h"

DHwifi dhWifi;

cDataTable DT;
DHFile     Config;

WiFiServer httpServer(80);

const int ACT = 2;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  Serial.println("SETUP");

  pinMode(ACT, OUTPUT);

  IPAddress ip(192, 168, 1, 201);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  String ssid   = "PistoniHome";          // your network SSID (name)
  String pass   = "giaco1iren1dario";     // your network password
  String remote = "192.168.1.200";        // remote server (arduino ethernet home)

  dhWifi.setup( ip, gateway, subnet, ssid, pass, remote );

  DT.setup();

  UpdateTime(0);      // update system time

  initHttpServer();

  RollingUpdateTerminals( 0 );

  DT.progBoilerACS.set(1);
  DT.progSummerAC.set(0);
  DT.progWinterPDC.set(0);
  DT.progWinterPDC_ECO.set(0);
  DT.progAllRooms.set(0);
  DT.progExternalLight.set(1);

  UpdateTime(0);  // update system time

  if ( month() >= 10 || month() <= 4) DT.progWinterFIRE.set(1);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  UpdateTime( 100 );

  if ( handleHttpServer() )
  {
    return;
  }
  
  digitalWrite(ACT, 1);

  DT.progBoilerACS.manualCheck();
  DT.progSummerAC.manualCheck();
  DT.progWinterFIRE.manualCheck();
  DT.progWinterPDC.manualCheck();
  DT.progWinterPDC_ECO.manualCheck();
  DT.progAllRooms.manualCheck();
  DT.progExternalLight.manualCheck();

  if (DT.progWinterFIRE) DT.progSummerAC.set(0);
  if (DT.progWinterPDC)  DT.progSummerAC.set(0);
  if (DT.progWinterPDC_ECO)  DT.progSummerAC.set(0);

  {// Run Managers
    
    if ( DT.progSummerAC ) // solo estate
    {
      Summer_Manager( 20 );
    }
    else                               // solo inverno
    {
      Winter_Manager( 20 );
    }
    BoilerACS_Manager( 20 );
    ExternalLight_Manager( 20 );
  }

  //----------------------------------------------------------------------------
  RollingSendValues( 2 );
  //----------------------------------------------------------------------------
  
  if ( handleHttpServer() )
  {
    return;
  }

  digitalWrite(ACT, 0);
  //----------------------------------------------------------------------------
  RollingUpdateTerminals( 5 );
  //----------------------------------------------------------------------------

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateTime( int sec )
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- UpdateTime --");

  time_t epoch = dhWifi.GetSystemTime();

  if (epoch > 0) setTime( epoch );
  DT.m_log.add( date_time() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollingUpdateTerminals( int sec )
{
  _CHECK_TIME_;

  static unsigned int i = 0;

  if ( i % 10 == 0 || i == 0 )   DT.UpdateT1( dhWifi.HttpRequest( "@get(1,99)") );
  if ( i % 10 == 2 || i == 0 )   DT.UpdateT2( dhWifi.HttpRequest( "@get(2,99)") );
  if ( i % 10 == 4 || i == 0 )   DT.UpdateT3( dhWifi.HttpRequest( "@get(3,99)") );
  if ( i % 10 == 6 || i == 0 )   DT.UpdateT4( dhWifi.HttpRequest( "@get(4,99)") );
  if ( i % 10 == 8 || i == 0 )   DT.UpdateT5( dhWifi.HttpRequest( "@get(5,99)") );
  
  if ( i % 4 == 1 || i == 0 )   DT.UpdateT6( dhWifi.HttpRequest( "@get(6,99)") ); //amperometri
  i++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollingSendValues( int sec )
{
  _CHECK_TIME_;

  static unsigned int i = 0;

  DT.rPdc.manualCheck();
  DT.rPdcHeat.manualCheck();
  DT.rPdcPompa.manualCheck();
  DT.rPdcNightMode.manualCheck();

  DT.rPompaPianoPrimo.manualCheck();
  DT.rPompaPianoTerra.manualCheck();
  DT.rBoilerACS.manualCheck();
  DT.rPompaCamino.manualCheck();

  DT.lightCorner.manualCheck();
  DT.lightSide.manualCheck();
  DT.lightLamp.manualCheck();
  DT.lightExtra.manualCheck();

  // le nnn sono a basso intervento 200 sec
  unsigned int i_hi =  i % 20;
  unsigned int i_low =  i % 200;

  if ( i_low == 10 ) DT.rPdc.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 12 ) DT.rPdcHeat.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 14 ) DT.rPdcPompa.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 16 ) DT.rPdcNightMode.sendRequest(&dhWifi, DT.m_log );

  if ( i_hi == 1 )    DT.rPompaPianoPrimo.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 2 )    DT.rPompaPianoTerra.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 20 )  DT.rBoilerACS.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 3 )    DT.rPompaCamino.sendRequest(&dhWifi, DT.m_log );

  if ( i_hi == 5 )    DT.evCameraM1.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 6 )    DT.evCameraM2.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 7 )    DT.evSala1.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 8 )    DT.evSala2.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 9 )    DT.evCucina.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 10 )   DT.evCameraS.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 11 )   DT.evCameraD1.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 12 )   DT.evCameraD2.sendRequest(&dhWifi, DT.m_log );

  if ( i_hi == 13 )   DT.lightCorner.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 14 )   DT.lightSide.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 15 )   DT.lightLamp.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 16 )   DT.lightExtra.sendRequest(&dhWifi, DT.m_log );

  i++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Summer_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- Summer_Manager ---------------");

  bool summerAC_pdc  = false;
  bool summerAC_pump = false;
  bool needPompa_pp  = false;
  bool allRoom = false;

  /**************************************************************************************************/
  if (DT.progSummerAC)
  {
    /**************************************************************************************************/
    // decido se accendere le pompe

    if ( DT.tPufferHi < 23 )
    {
      needPompa_pp = true;      // economy
      allRoom = true;
    }
    else
    {
      if ( DT.tInletFloor > 20 )  // minima t Acqua raffreddata
      {
        summerAC_pdc = true;
        summerAC_pump = true;
        allRoom = DT.progAllRooms;
      }
      if ( DT.tReturnFloor > 21 )
      {
        summerAC_pump = true;
        allRoom = DT.progAllRooms;
      }
    }
    /**************************************************************************************************/
    DT.m_log.add("summerAC_pdc [" +  String(summerAC_pdc) + "] summerAC_pump [" +  String(summerAC_pump) + "] tInletFloor: " + String( DT.tInletFloor ) + " tSala: " + String( DT.tSala ) + " tReturnFloor: " + String( DT.tReturnFloor ));
    DT.m_log.add("needPompa_pp [" +  String(needPompa_pp) + "] tPufferHi: " + String( DT.tPufferHi ));
  }
  /**************************************************************************************************/
  // attuatori
  DT.evSala1.set(allRoom);
  DT.evSala2.set(allRoom);
  DT.evCucina.set(summerAC_pump || allRoom);

  DT.evCameraM1.set(summerAC_pump || allRoom);
  DT.evCameraM2.set(summerAC_pump || allRoom);
  DT.evCameraS.set (summerAC_pump || allRoom);
  DT.evCameraD1.set(summerAC_pump || allRoom);
  DT.evCameraD2.set(summerAC_pump || allRoom);

  DT.rPompaPianoPrimo.set( needPompa_pp );

  /**************************************************************************************************/
  // accendo PDC
  DT.rPdc.set( summerAC_pdc );
  DT.rPdcNightMode.set( summerAC_pdc );
  DT.rPdcHeat.set( false );
  DT.rPdcPompa.set( summerAC_pump );
  /**************************************************************************************************/
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BoilerACS_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- BoilerACS_Manager ---------------");

  bool boilerACS = false;
  /**************************************************************************************************/
  if (DT.progBoilerACS)
  {
    //decido se accendere il boiler solo di notte e solo se il camino non funziona
    if ( hour() < 7 )
    {
      boilerACS = true;
      DT.m_log.add("Condizione ON hour:" + String( hour() ) + "< 7");
    }
    if ( DT.tReturnFireplace > 25 )
    {
      boilerACS = false;
      DT.m_log.add("Condizione OFF DT.ReturnFireplace:" + String( DT.tReturnFireplace ) + "> 25");
    }
  }
  /**************************************************************************************************/
  DT.m_log.add("BoilerACS [" + String( boilerACS ) + "]");

  // boiler
  DT.rBoilerACS.set( boilerACS );
}

/******************************************************************************************************************************************************************/
void Winter_Manager( int sec )
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- Winter_Manager --------------------");

  bool sala = false;
  bool sala2 = false;
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

  bool AllIn = DT.progAllRooms;

  if (DT.progWinterFIRE || DT.progWinterPDC || DT.progWinterPDC_ECO)
  {
    //////////////////////////////////////////////////////////////////////////////////
    //decido se accendere le stanze
    String str = "Condizione";
    if ( DT.tSala < DT.tSala.setPoint() )
    {
      str += " tSala " + String(DT.tSala) + " < " + String(DT.tSala.setPoint());
      sala = true;
    }
    if ( DT.tSala < DT.tSala.setPoint() - 1 )
    {
      sala2 = true;
    }
    if ( DT.tCucina < DT.tCucina.setPoint() )
    {
      str += " tCucina " + String(DT.tCucina) + " < " + String(DT.tCucina.setPoint());
      cucina = true;
    }
    if ( DT.tCameraS < DT.tCameraS.setPoint() )
    {
      str += " tCameraS " + String(DT.tCameraS) + " < " + String(DT.tCameraS.setPoint());
      cameraS = true;
    }
    if ( DT.tCameraD < DT.tCameraD.setPoint() )
    {
      str += " tCameraD " + String(DT.tCameraD) + " < " + String(DT.tCameraD.setPoint());
      cameraD = true;
    }
    if ( DT.tCameraD < DT.tCameraD.setPoint() - 2 )
    {
      cameraD2 = true;
    }
    if ( DT.tCameraM < DT.tCameraM.setPoint() )
    {
      str += " tCameraM " + String(DT.tCameraM) + " < " + String(DT.tCameraM.setPoint());
      cameraM = true;
    }
    if ( DT.tCameraM < DT.tCameraM.setPoint() - 2 )
    {
      cameraM2 = true;
    }
    if ( DT.tBagno < DT.tBagno.setPoint() )
    {
      str += " tBagno " + String(DT.tBagno) + " < " + String(DT.tBagno.setPoint());
      bagno = true;
    }
    DT.m_log.add(str);

    //////////////////////////////////////////////////////////////////////////////////
    // decido se accendere/spegnere pompa piano primo
    needPompa_pp = ( sala || cucina || bagno || cameraS || cameraD || cameraM );
    if ( DT.tInputMixer < 28 && DT.tPufferHi < 28 && DT.tReturnFireplace < 28 )   // non ho temperatura
    {
      DT.m_log.add("Condizione Pompa PP insufficiente: tInletFloor: " + String(DT.tInletFloor) + " tReturnFloor: " + String(DT.tReturnFloor) );
      needPompa_pp = false;
    }
    if ( (DT.tReturnFloor > 28) )  // ritorno troppo alto - non ne ho bisogno
    {
      DT.m_log.add("Stop Pompa: ritorno troppo alto tReturnFloor: " + String(DT.tReturnFloor) );
      needPompa_pp = false;
    }
    if ( DT.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
    {
      DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + String(DT.tInletFloor) + " > 35" );
      needPompa_pp = false;
    }
    if ( DT.tReturnFireplace < 35 && hour() < 5 ) // fuori oario
    {
      DT.m_log.add("Stop Pompa: orario " + String( hour() ) );
      needPompa_pp = false;
    }
    if ( DT.tPufferLow > 55 )   // emergenza
    {
      DT.m_log.add("Emergenza tPufferLow > 55 ");
      needPompa_pp = true;
      needPompa_pt = true;
      AllIn = true;
    }
    DT.m_log.add( "NeedPompa_pp: [" + String(needPompa_pp) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    //decido se accendere PDC
    needPdc = DT.progWinterPDC && ( sala || cucina || bagno );
    needPdc = needPdc || ( DT.progWinterPDC_ECO && (sala || cucina || bagno) && DT.tExternal > 7 );

    if ( needPompa_pp )
    {
      DT.m_log.add("PDC suspended - Fire enought ");
      needPdc = false;
    }
    DT.m_log.add( "NeedPdc: [" + String(needPdc) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    // decido se accendere pompa camino
    DT.m_log.add("Condizione Pompa Camino: tReturnFireplace " + String(DT.tReturnFireplace) + " - " + "tPufferLow " + String(DT.tPufferLow) );
    if ( DT.tPufferLow < 45 && DT.tReturnFireplace > 34 && DT.tReturnFireplace > DT.tPufferLow + 5 )
    {
      needPCamino = true;
    }
    DT.m_log.add( "NeedPCamino: [" + String(needPCamino) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    // decido se accendere piano terra
    if ( DT.tPufferLow > 45 && DT.tReturnFireplace > 45 )
    {
      DT.m_log.add("Condizione DT.tPufferLow > 45 && DT.tReturnFireplace > 45");
      needPompa_pt = true;
    }
    DT.m_log.add( "NeedPompa_pt: [" + String(needPompa_pt) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    // decido se attivare le elettrovalbole primo piano
    bool NeedEv = false;
    if ( DT.tInletFloor > 25 )
    {
      NeedEv = true;
    }
    DT.m_log.add( "NeedEv: [" + String(NeedEv) + "]" );

    cameraM   = (cameraM &&  NeedEv) || AllIn;
    cameraM2  = (cameraM2 && NeedEv) || AllIn;
    sala      = (sala && NeedEv) || AllIn;
    sala2     = (sala2 && NeedEv) || AllIn;
    cucina    = (cucina && NeedEv) || AllIn;
    cameraS   = (cameraS && NeedEv) || AllIn;
    cameraD   = (cameraD && NeedEv) || AllIn;
    cameraD2  = (cameraD2 && NeedEv) || AllIn;
  }

  //**********************************************************************
  // attuatori -----------------------------------------------------------------------
  DT.evCameraM1.set(cameraM);
  DT.evCameraM2.set(cameraM2);
  DT.evSala1.set(sala);
  DT.evSala2.set(sala2);
  DT.evCucina.set(cucina);
  DT.evCameraS.set(cameraS);
  DT.evCameraD1.set(cameraD);
  DT.evCameraD2.set(cameraD2);

  // comandi semimanuali centrale -----------------------------------------------------
  // accendo pompa pp
  DT.rPompaPianoPrimo.set( needPompa_pp );
  //piano terra
  DT.rPompaPianoTerra.set( needPompa_pt );
  // accendo PDC
  DT.rPdc.set( needPdc );
  // heat
  DT.rPdcHeat.set( needPdc );
  //pompa
  DT.rPdcPompa.set( needPdc );
  //night
  DT.rPdcNightMode.set( needPdc );
  //camino
  DT.rPompaCamino.set( needPCamino );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExternalLight_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- ExternalLight_Manager --------------------");

  bool lightSide = false;
  bool lightLamp = false;

  if (DT.progExternalLight)
  {
    /**************************************************************************************************/
    DT.m_log.add("-- darkExternal: " + String(DT.lightExternal) + " Request [" + String( 40 + 20 * DT.lightSide) + "]" );
    if ( DT.lightExternal > 40 + 20 * DT.lightSide ) // isteresi
    {
      lightSide = true;
      lightLamp = true;
    }

    if ( hour() < 12 )
    {
      lightLamp = false;
    }

    /**************************************************************************************************/
    DT.m_log.add("-- LightLamp [" +  String(lightLamp) + "]  LightSide [" +  String(lightSide) + "]" );
  }

  // attuatori
  DT.lightCorner.set(lightSide);
  DT.lightSide.set(lightSide);
  DT.lightLamp.set(lightLamp);
  DT.lightExtra.set(lightLamp);
}
