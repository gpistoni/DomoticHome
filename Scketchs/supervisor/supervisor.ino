#define _CHECK_TIME_   static unsigned long last = 0;\
  if ( millis() - last < sec * 1000 ) return;\
  last = millis();

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Time.h>

#include "dhwifi.h"
#include "dhconfig.h"
#include "DataTable.h"
#include "functions.h"
#include "httpServer2.h"
#include "googleScript.h"

DHwifi dhWifi;

cDataTable DT;
DHFile     Config;

WiFiServer httpServer(80);

const int ACT = 2;

//////////////////////////////////////////////////////////////////////////////////
const char* host = "script.google.com";
String GScriptId = "/macros/s/AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM/exec?";
const char* fingerprint = "FD:8C:AC:55:64:BE:30:57:9A:27:53:52:62:E1:CD:26:82:15:A2:DB";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(ACT, OUTPUT);
  digitalWrite(ACT, 0);

  Serial.begin(115200);
  Serial.println();

  IPAddress ip(192, 168, 0, 202);
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

  if ( month() >= 9 || month() < 4) DT.progWinterFIRE.set(1);

  ScriptValuesLabels();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  void loop()
  {
  digitalWrite(ACT, 1);

  if ( handleHttpServer() )
  {
    BoilerACS_Manager( 20 );
    Summer_Manager( 20 );
    if (DT.progWinterFIRE || DT.progWinterPDC )        Winter_Manager( 20 );
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
  Summer_Manager( 60 );
  Winter_Manager( 60 );
  ExternalLight_Manager( 60 );

  RollingSendValues( 2 );
  digitalWrite(ACT, 0);
  RollingUpdateTerminals( 5 );

  ScriptValues(60);
  }
*/
void loop()
{
  RollingUpdateTerminals( 30 );
  ScriptValues(60 * 10);
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

  if ( year() < 2000 )
    UpdateTime();

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

  if ( i % nnn == 0 )  DT.rPdc.send(&dhWifi, DT.m_log );
  if ( i % nnn == 10 ) DT.rPdcHeat.send(&dhWifi, DT.m_log );
  if ( i % nnn == 20 ) DT.rPdcPompa.send(&dhWifi, DT.m_log );
  if ( i % nnn == 30 ) DT.rPdcNightMode.send(&dhWifi, DT.m_log );
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
void ScriptValuesLabels()
{
  GoogleScript GoogleClient;
  GoogleClient.Connect(host, fingerprint);
  String url = GScriptId + "sheet=" + "temp" + "&v1=" + "tExternal" + "&v2=" + "tSala" + "&v3=" + "tFloorIN"  + "&v4=" + "tFloorRET" + "&v5=" + "tPufferHi" + "&v6=" + "tPufferLow" + "&v7=" + "tReturnFireplace";
  DT.m_log.add(url);
  GoogleClient.Post(url);
}

void ScriptValues(int sec)
{
  _CHECK_TIME_;
  if ( DT.tSala > 0 && DT.tInletFloor  > 0 && DT.tReturnFloor > 0 && DT.tPufferHi > 0)
  {
    GoogleScript GoogleClient;
    GoogleClient.Connect(host, fingerprint);
    String url = GScriptId + "sheet=" + "temp" + "&v1=" + DT.tExternal + "&v2=" + DT.tSala + "&v3=" + DT.tInletFloor + "&v4=" + DT.tReturnFloor + "&v5=" + DT.tPufferHi + "&v6=" + DT.tPufferLow + "&v7=" + DT.tReturnFireplace;
    DT.m_log.add(url);
    GoogleClient.Post(url);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Summer_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- Summer_Manager --");
  {
    //if ( DT.pPDC_man ) return;
    //  digitalClockDisplay();
    //  Serial.println("PDC_Manager");
    //
    //  DT.rPdc.set(0);
    //  DT.rPdcPompa.set(0);
    //
    //  //decido se accendere la pdc
    //  if ( month() == 6 ||  month() == 7 || month() == 8 ) // solo estate
    //  {
    //    if ( DT.tExternal > 30 && DT.tInletFloor > 20 )   // t esterne, minima t Acqua raffreddata
    //    {
    //      Serial.println("Condizione H1");
    //      DT.rPdc.set(1);
    //      DT.rPdcCool0_Heat1.set(0);
    //      DT.rPdcPompa.set(1);
    //      DT.rPdcNightMode.set(1);
    //    }
    //    if ( DT.tInletFloor < DT.tReturnFloor - 1 )
    //    {
    //      Serial.println("Condizione H2");
    //      DT.rPdcPompa.set(1);
    //    }
    //  }
    //
    //  dhWifi.HttpRequest( DT.rPdc.getS() );
    //  dhWifi.HttpRequest( DT.rPdcCool0_Heat1.getS() );
    //  dhWifi.HttpRequest( DT.rPdcPompa.getS() );
    //  dhWifi.HttpRequest( DT.rPdcNightMode.getS() );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BoilerACS_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- BoilerACS_Manager --");

  static bool boilerACS = false;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummerAC_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- SummerAC_Manager --");

  static bool summerAC = false;
  /**************************************************************************************************/
  // decido se accendere le pompe
  if ( DT.tExternal > 24 && DT.tSala > 26 &&  DT.tReturnFloor > 20 - summerAC * 1 ) // isteresi
  {
    summerAC = true;
  }
  /**************************************************************************************************/

  DT.m_log.add("summerAC [" +  String(summerAC) + "] tExternal: " + String( DT.tExternal ) + " tSala: " + String( DT.tSala ) + " tReturnFloor: " + String( DT.tReturnFloor ));

  // attuatori
  DT.evCameraM1.set(summerAC);
  DT.evSala1.set(summerAC);
  DT.evSala2.set(summerAC);
  DT.evCucina.set(summerAC);
  DT.evCameraS.set(summerAC);
  DT.evCameraD1.set(summerAC);

  // accendo PDC
  DT.rPdc.set( summerAC );
  DT.rPdcHeat.set( false );
  DT.rPdcPompa.set( summerAC );
  DT.rPdcNightMode.set( true );
}

/******************************************************************************************************************************************************************/
void Winter_Manager( int sec )
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- Winter_Manager --");

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
    DT.m_log.add("Condizione Pompa PP: tInputMixer: " + String(DT.tInputMixer) + " tPufferHi: " + String(DT.tPufferHi) + " tReturnFireplace: " + String(DT.tReturnFireplace) );
    if ( DT.tInputMixer > 24 || DT.tPufferHi > 25 || DT.tReturnFireplace > 24 )
    {
      DT.m_log.add("Condizione Pompa PP: tInletFloor: " + String(DT.tInletFloor) + " tReturnFloor: " + String(DT.tReturnFloor) );

      if ( (DT.tInletFloor - DT.tReturnFloor) < 2 && minute() % 10 != 0 )  // ritorno troppo alto - non ne ho bisogno
      {
        DT.m_log.add("Stop Pompa: ritorno troppo alto tReturnFloor: " + String(DT.tReturnFloor) + " tInletFloor: " + String(DT.tInletFloor) );
        needPompa_pp = false;
      }
      if ( DT.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
      {
        DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + String(DT.tInletFloor) + " > 35" );
        needPompa_pp = false;
      }
    }
    else // non ho temperatura
    {
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
    if ( DT.tPufferLow < 45 && DT.tReturnFireplace > 35 && DT.tReturnFireplace > DT.tPufferLow + 4 )
    {
      needPCamino = true;
    }
    DT.m_log.add( "NeedPCamino: [" + String(needPCamino) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    //decido se accendere sulla lavanderia
    DT.m_log.add("Condizione tPufferLow " +  String(DT.tPufferHi)  + " > 46 ");
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
  DT.m_log.add("-------------------- ExternalLight_Manager --");

  bool lightSide = false;
  bool lightLamp = false;

  if (DT.progExternalLight)
  {
    /**************************************************************************************************/
    // decido se accendere le luci
    if ( DT.lightExternal < 1 + 2 * DT.lightSide ) // isteresi
    {
      lightSide = true;
      lightLamp = true;
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
