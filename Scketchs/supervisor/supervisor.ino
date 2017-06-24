//supervisor

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
  pinMode(ACT, OUTPUT);
  digitalWrite(ACT, 0);

  Serial.begin(115200);
  Serial.println();

  IPAddress ip(192, 168, 0, 201);
  IPAddress gateway(192, 168, 0, 254);
  IPAddress subnet(255, 255, 255, 0);

  String ssid   = "PistoniHome";          // your network SSID (name)
  String pass   = "giaco.iren.dario";     // your network password
  String remote = "192.168.0.200";        // remote server

  dhWifi.setup( ip, gateway, subnet, ssid, pass, remote );

  DT.setup();

  UpdateTime();      // update system time

  initHttpServer();

  RollingUpdateTerminals( 0 );

  DT.progBoilerACS.set(1);
  DT.progSummerAC.set(0);
  DT.progWinterPDC.set(0);
  DT.progAllRooms.set(0);
  DT.progExternalLight.set(1);

  UpdateTime();      // update system time

  if ( month() >= 10 || month() <= 4) DT.progWinterFIRE.set(1);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  digitalWrite(ACT, 1);

  if ( handleHttpServer() )
  {
    if ( month() == 6 ||  month() == 7 || month() == 8 ) // solo estate
    {
      Summer_Manager( 20 );
    }
    else                               // solo inverno
    {
      Winter_Manager( 20 );
    }
    BoilerACS_Manager( 20 );
    ExternalLight_Manager( 20 );
    return;
  }

  DT.progBoilerACS.manualCheck();
  DT.progSummerAC.manualCheck();
  DT.progWinterFIRE.manualCheck();
  DT.progWinterPDC.manualCheck();
  DT.progAllRooms.manualCheck();
  DT.progExternalLight.manualCheck();

  if (DT.progWinterFIRE) DT.progSummerAC.set(0);
  if (DT.progWinterPDC)  DT.progSummerAC.set(0);

  BoilerACS_Manager( 60 );
  ExternalLight_Manager( 60 );

  if ( month() == 6 ||  month() == 7 || month() == 8 ) // solo estate
  {
    Summer_Manager( 60 );
  }
  else                               // solo inverno
  {
    Winter_Manager( 60 );
  }

  RollingSendValues( 2 );
  digitalWrite(ACT, 0);
  RollingUpdateTerminals( 4 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateTime()
{
  DT.m_log.add("-------------------- UpdateTime --");

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollingUpdateTerminals( int sec )
{
  _CHECK_TIME_;

  static unsigned int i = 0;

  if ( i % 6 == 0 || i == 0 )   DT.UpdateT1( dhWifi.HttpRequest( "@get(1,99)") );
  if ( i % 6 == 1 || i == 0 )   DT.UpdateT2( dhWifi.HttpRequest( "@get(2,99)") );
  if ( i % 6 == 2 || i == 0 )   DT.UpdateT3( dhWifi.HttpRequest( "@get(3,99)") );
  if ( i % 6 == 3 || i == 0 )   DT.UpdateT4( dhWifi.HttpRequest( "@get(4,99)") );
  if ( i % 6 == 4 || i == 0 )   DT.UpdateT5( dhWifi.HttpRequest( "@get(5,99)") );
  if ( i % 6 == 5 || i == 0 )   DT.UpdateT6( dhWifi.HttpRequest( "@get(6,99)") );

  i++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollingSendValues( int sec )
{
  _CHECK_TIME_;

  static unsigned int i = 0;
  unsigned int n = 20;
  unsigned int nnn = 200;

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

  if ( i % nnn == 10 )  DT.rPdc.send(&dhWifi, DT.m_log );
  if ( i % nnn == 12 ) DT.rPdcHeat.send(&dhWifi, DT.m_log );
  if ( i % nnn == 14 ) DT.rPdcPompa.send(&dhWifi, DT.m_log );
  if ( i % nnn == 16 ) DT.rPdcNightMode.send(&dhWifi, DT.m_log );

  if ( i % n == 1 )    DT.rPompaPianoPrimo.send(&dhWifi, DT.m_log );
  if ( i % n == 2 )    DT.rPompaPianoTerra.send(&dhWifi, DT.m_log );
  if ( i % nnn == 60 ) DT.rBoilerACS.send(&dhWifi, DT.m_log );
  if ( i % n == 3 )    DT.rPompaCamino.send(&dhWifi, DT.m_log );

  if ( i % n == 5 )    DT.evCameraM1.send(&dhWifi, DT.m_log );
  if ( i % n == 6 )    DT.evCameraM2.send(&dhWifi, DT.m_log );
  if ( i % n == 7 )    DT.evSala1.send(&dhWifi, DT.m_log );
  if ( i % n == 8 )    DT.evSala2.send(&dhWifi, DT.m_log );
  if ( i % n == 9 )    DT.evCucina.send(&dhWifi, DT.m_log );
  if ( i % n == 10 )   DT.evCameraS.send(&dhWifi, DT.m_log );
  if ( i % n == 11 )   DT.evCameraD1.send(&dhWifi, DT.m_log );
  if ( i % n == 12 )   DT.evCameraD2.send(&dhWifi, DT.m_log );

  if ( i % n == 13 )   DT.lightCorner.send(&dhWifi, DT.m_log );
  if ( i % n == 14 )   DT.lightSide.send(&dhWifi, DT.m_log );
  if ( i % n == 15 )   DT.lightLamp.send(&dhWifi, DT.m_log );
  if ( i % n == 16 )   DT.lightExtra.send(&dhWifi, DT.m_log );

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
  /**************************************************************************************************/
  if (DT.progSummerAC)
  {
    /**************************************************************************************************/
    // decido se accendere le pompe

    if ( DT.tPufferHi < 23 )
    {
      needPompa_pp = true;      // economy
    }
    else
    {
      if ( DT.tInletFloor > 22 )  // minima t Acqua raffreddata
      {
        summerAC_pdc = true;
        summerAC_pump = true;
      }
      if ( DT.tReturnFloor > 22 )
      {
        summerAC_pump = true;
      }
    }
    /**************************************************************************************************/
    DT.m_log.add("summerAC_pdc [" +  String(summerAC_pdc) + "] summerAC_pump [" +  String(summerAC_pump) + "] tInletFloor: " + String( DT.tInletFloor ) + " tSala: " + String( DT.tSala ) + " tReturnFloor: " + String( DT.tReturnFloor ));
    DT.m_log.add("needPompa_pp [" +  String(needPompa_pp) + "] tPufferHi: " + String( DT.tPufferHi ));
  }
  /**************************************************************************************************/
  // attuatori
  DT.evSala1.set(needPompa_pp);
  DT.evSala2.set(needPompa_pp);
  DT.evCucina.set(summerAC_pump || needPompa_pp);

  DT.evCameraM1.set(summerAC_pump || needPompa_pp);
  DT.evCameraM2.set(summerAC_pump || needPompa_pp);
  DT.evCameraS.set (summerAC_pump || needPompa_pp);
  DT.evCameraD1.set(summerAC_pump || needPompa_pp);
  DT.evCameraD2.set(summerAC_pump || needPompa_pp);

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

  if (DT.progWinterFIRE || DT.progWinterPDC )
  {
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
    needPompa_pp = ( sala || cucina || bagno || cameraS || cameraD || cameraM );
    if ( DT.tInputMixer < 25 && DT.tPufferHi < 25 && DT.tReturnFireplace < 25 )   // non ho temperatura
    {
      DT.m_log.add("Condizione Pompa PP insufficiente: tInletFloor: " + String(DT.tInletFloor) + " tReturnFloor: " + String(DT.tReturnFloor) );
      needPompa_pp = false;
    }
    if ( (DT.tInletFloor > 25) && (DT.tInletFloor - DT.tReturnFloor) < 2 && minute() % 10 != 0 )  // ritorno troppo alto - non ne ho bisogno
    {
      DT.m_log.add("Stop Pompa: ritorno troppo alto tReturnFloor: " + String(DT.tReturnFloor) + " tInletFloor: " + String(DT.tInletFloor) );
      needPompa_pp = false;
    }
    if ( DT.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
    {
      DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + String(DT.tInletFloor) + " > 35" );
      needPompa_pp = false;
    }
    if ( hour() > 1 && hour() < 4 ) // fuori oario
    {
      DT.m_log.add("Stop Pompa: orario " + String( hour() ) );
      needPompa_pp = false;
    }
    if ( DT.tPufferLow > 55 )   // emergenza
    {
      DT.m_log.add("Emergenza tPufferLow > 50 ");
      needPompa_pp = sala = sala2 = cucina = cameraS = cameraD = cameraM = true;
    }
    DT.m_log.add( "NeedPompa_pp: [" + String(needPompa_pp) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    needPdc = DT.progWinterPDC && (sala || cucina || bagno);
    if ( needPompa_pp )
    {
      DT.m_log.add("PDC suspended - Fire enought ");
      needPdc = false;
    }
    DT.m_log.add( "NeedPdc: [" + String(needPdc) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    DT.m_log.add("Condizione Pompa Camino: tReturnFireplace " + String(DT.tReturnFireplace) + " - " + "tPufferLow " + String(DT.tPufferLow) );
    if ( DT.tPufferLow < 45 && DT.tReturnFireplace > 40 && DT.tReturnFireplace > DT.tPufferLow + 4 )
    {
      needPCamino = true;
    }
    DT.m_log.add( "NeedPCamino: [" + String(needPCamino) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    //decido se accendere sulla lavanderia
    DT.m_log.add("Condizione DT.tPufferLow > 45 && DT.tReturnFireplace > 40");
    if ( DT.tPufferLow > 45 && DT.tReturnFireplace > 40 )
    {
      needPompa_pt = true;
    }
    DT.m_log.add( "NeedPompa_pt: [" + String(needPompa_pt) + "]" );
  }

  bool AllIn = DT.progAllRooms;

  cameraM   = (cameraM && ( needPompa_pp )) || AllIn;
  cameraM2  = (cameraM2 && ( needPompa_pp )) || AllIn;
  sala      = (sala && ( needPompa_pp || needPdc )) || AllIn;
  sala2     = (sala2 && ( needPompa_pp || needPdc )) || AllIn;
  cucina    = (cucina && ( needPompa_pp || needPdc )) || AllIn;
  cameraS   = (cameraS && ( needPompa_pp || needPdc )) || AllIn;
  cameraD   = (cameraD && ( needPompa_pp || needPdc )) || AllIn;
  cameraD2  = (cameraD2 && ( needPompa_pp )) || AllIn;

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
    // decido se accendere le luci
    if ( DT.lightExternal > 8 + 2 * DT.lightSide ) // isteresi
    {
      lightSide = true;
      lightLamp = true;
    }

    if ( hour() > 21 || hour() < 5 )
    {
      lightSide = true;
    }
    if ( hour() < 18 )
    {
      lightLamp = false;
    }

    /**************************************************************************************************/
    DT.m_log.add("-- LightSide [" +  String(lightSide) + "] + lightExternal: " + String(DT.lightExternal) );
    DT.m_log.add("-- LightLamp [" +  String(lightLamp) + "]" );
  }

  // attuatori
  DT.lightCorner.set(lightSide);
  DT.lightSide.set(lightSide);
  DT.lightLamp.set(lightLamp);
  DT.lightExtra.set(lightLamp);
}
