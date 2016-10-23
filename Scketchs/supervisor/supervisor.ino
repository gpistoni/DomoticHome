#define _CHECK_TIME_   static unsigned long last = 0;\
  if ( millis() - last < sec * 1000 ) return;\
  last = millis();

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <WiFiUdp.h>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

  Config.LoadFile();
  DT.setup();

  Config.ReadValue("T1");
  Config.SaveFile();

  UpdateTime();      // update system time

   initHttpServer();

  RollingUpdateTerminals( 0 );

  DT.progBoilerSanitaria.set(1);
  
  if ( month() >= 9 || month() < 4) DT.progWinterFIRE.set(1);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  digitalWrite(ACT, 1);

  if ( handleHttpServer() )
  {
    if (DT.progBoilerSanitaria)                        BoilerSanitaria_Manager( 20 );
    if (DT.progSummerAC)                               Summer_Manager( 20 );
    if (DT.progWinterFIRE || DT.progWinterPDC )        Winter_Manager( 20 );
    return;
  }

  RollingSendValues( 1 );
  RollingUpdateTerminals( 15 );
  digitalWrite(ACT, 0);


  DT.progBoilerSanitaria.manualCheck(  DT.progBoilerSanitaria );
  DT.progSummerAC.manualCheck( DT.progSummerAC );
  DT.progWinterFIRE.manualCheck( DT.progWinterFIRE );
  DT.progWinterPDC.manualCheck( DT.progWinterPDC );
  DT.progAllRooms.manualCheck( DT.progAllRooms );
  DT.prog5.manualCheck( DT.prog5 );

  if (DT.progWinterFIRE) DT.progSummerAC.set(0);
  if (DT.progWinterPDC)  DT.progSummerAC.set(0);

  if (DT.progBoilerSanitaria)                        BoilerSanitaria_Manager( 60 );
  if (DT.progSummerAC)                               Summer_Manager( 60 );
  if (DT.progWinterFIRE || DT.progWinterPDC )        Winter_Manager( 60 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateTime()
{
  DT.m_log.add("-- UpdateTime --");

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollingUpdateTerminals( int sec )
{
   _CHECK_TIME_;

  if (year() < 2000 )
    UpdateTime();

  static unsigned int i = 0;

  if ( i % 4 == 0 || i == 0 )   DT.UpdateT1( dhWifi.HttpRequest( "@get(1,99)") );
  if ( i % 4 == 1 || i == 0 )   DT.UpdateT3( dhWifi.HttpRequest( "@get(3,99)") );
  if ( i % 4 == 2 || i == 0 )   DT.UpdateT4( dhWifi.HttpRequest( "@get(4,99)") );
  if ( i % 4 == 3 || i == 0 )   DT.UpdateT5( dhWifi.HttpRequest( "@get(5,99)") );

  i++;
}

void RollingSendValues( int sec )
{
  _CHECK_TIME_;
  static unsigned int i = 0;
  static unsigned int n = 20;

  if ( i % n == 0 )   DT.rPdc.send(&dhWifi, DT.m_log );
  if ( i % n == 1 )   DT.rPdcHeat.send(&dhWifi, DT.m_log );
  if ( i % n == 2 )   DT.rPdcPompa.send(&dhWifi, DT.m_log );
  if ( i % n == 3 )   DT.rPdcNightMode.send(&dhWifi, DT.m_log );
  if ( i % n == 4 )   DT.rPompaPianoPrimo.send(&dhWifi, DT.m_log );
  if ( i % n == 5 )   DT.rPompaPianoTerra.send(&dhWifi, DT.m_log );
  if ( i % n == 6 )   DT.rBoilerSanitaria.send(&dhWifi, DT.m_log );
  if ( i % n == 7 )   DT.rPompaCamino.send(&dhWifi, DT.m_log );
  if ( i % n == 8 )   DT.evCameraM1.send(&dhWifi, DT.m_log );
  if ( i % n == 9 )   DT.evCameraM2.send(&dhWifi, DT.m_log );
  if ( i % n == 11 )   DT.evSala1.send(&dhWifi, DT.m_log );
  if ( i % n == 12 )   DT.evSala2.send(&dhWifi, DT.m_log );
  if ( i % n == 13 )   DT.evCucina.send(&dhWifi, DT.m_log );
  if ( i % n == 14 )   DT.evCameraS.send(&dhWifi, DT.m_log );
  if ( i % n == 15 )   DT.evCameraD1.send(&dhWifi, DT.m_log );
  if ( i % n == 16 )   DT.evCameraD2.send(&dhWifi, DT.m_log );

  i++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Summer_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-- SummerPP_Manager --");

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BoilerSanitaria_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("--BoilerSanitaria_Manager--");

  static bool boilerACS = false;
  /**************************************************************************************************/
  //decido se accendere il boiler solo di notte e solo se il camino non funziona
  if ( hour() < 7 &&  DT.tReturnFireplace < 30  + boilerACS * 5 ) //isteresi
  {
    boilerACS = true;
  }
  else
  {
    boilerACS = false;
  }
  /**************************************************************************************************/

  DT.m_log.add("BoilerACS [" + String(boilerACS) + "]  hour:" + String( hour() ) + " tReturnFireplace: " + String( DT.tReturnFireplace ) );

  // boiler
  DT.rBoilerSanitaria.manualCheck( boilerACS );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SummerAC_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-- SummerAC_Manager --");

  static bool summerAC = false;

  /**************************************************************************************************/
  // decido se accendere le pompe
  if ( DT.tExternal > 24 && DT.tSala > 26 &&  DT.tReturnFloor > 20 - summerAC * 1 ) //isteresi
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
  DT.rPdc.manualCheck( summerAC );
  DT.rPdcHeat.set( false );
  DT.rPdcPompa.set( summerAC );
  DT.rPdcNightMode.manualCheck( true );
}

/******************************************************************************************************************************************************************/
void Winter_Manager( int sec )
{
  _CHECK_TIME_;
  DT.m_log.add("-- WinterPP_Manager --");

  digitalWrite(ACT, 0);

  bool sala = false;
  bool sala2 = false;
  bool cucina = false;
  bool cameraS = false;
  bool cameraD = false;
  bool cameraD2 = false;
  bool cameraM = false;
  bool cameraM2 = false;
  bool bagno = false;

  //decido se accendere le stanze
  String str = "Condizione";
  if ( DT.tSala < DT.tSala.setPoint() )
  {
    str += " tSala " + String(DT.tSala) + " < " + String(DT.tSala.setPoint());
    sala = true;
  }
  if ( DT.tSala < DT.tSala.setPoint() - 1 )
  {
    str += " tSala2 " + String(DT.tSala) + " << " + String(DT.tSala.setPoint());
    sala2 = true;
  }
  if ( DT.tCucina < DT.tCucina.setPoint() )
  {
    str += " tCucina " + String(DT.tCucina) + " < " + String(DT.tCucina.setPoint());
    cucina = true;
  }
  if ( !sala2 && DT.tCameraS < DT.tCameraS.setPoint() )
  {
    str += " tCameraS " + String(DT.tCameraS) + " < " + String(DT.tCameraS.setPoint());
    cameraS = true;
  }
  if (  !sala2 && DT.tCameraD < DT.tCameraD.setPoint() )
  {
    str += " tCameraD " + String(DT.tCameraD) + " < " + String(DT.tCameraD.setPoint());
    cameraD = true;
  }
  if ( !sala2 && DT.tCameraD < DT.tCameraD.setPoint() - 1 )
  {
    str += " tCameraD2 " + String(DT.tCameraD) + " << " + String(DT.tCameraD.setPoint());
    cameraD2 = true;
  }
  if ( !sala2 && DT.tCameraM < DT.tCameraM.setPoint() )
  {
    str += " tCameraM " + String(DT.tCameraM) + " < " + String(DT.tCameraM.setPoint());
    cameraM = true;
  }
  if ( !sala2 && DT.tCameraM < DT.tCameraM.setPoint() - 1 )
  {
    str += " tCameraM " + String(DT.tCameraM) + " << " + String(DT.tCameraM.setPoint()) ;
    cameraM2 = true;
  }
  if ( DT.tBagno < DT.tBagno.setPoint() )
  {
    str += " tBagno " + String(DT.tBagno) + " < " + String(DT.tBagno.setPoint());
    bagno = true;
  }
  DT.m_log.add(str);

  //////////////////////////////////////////////////////////////////////////////////
  bool needPompa_pp = ( sala || cucina || bagno || cameraS || cameraD || cameraM );
  if ( DT.tPufferLow > 48 )   // emergenza
  {
    DT.m_log.add("Emergenza tPufferLow > 48 ");
    needPompa_pp = sala = cucina = cameraS = cameraD = cameraM = true;
  }

  DT.m_log.add("Condizione Pompa PP: tInputMixer:" + String(DT.tInputMixer) + " tPufferHi:" + String(DT.tPufferHi) + " tReturnFireplace:" + String(DT.tReturnFireplace) );
  if ( DT.tInputMixer > 25 || DT.tPufferHi > 25 || DT.tReturnFireplace > 25 )
  {
    if ( DT.tReturnFloor > 28 )  // ritorno troppo alto - non ne ho bisogno
    {
      DT.m_log.add("Stop Pompa: ritorno troppo alto tReturnFloor:" + String(DT.tReturnFloor) + " > 28" );
      needPompa_pp = false;
    }
    if ( DT.tInletFloor > 35 )  // 35 è la sicurezza, 29 la t massima dopo al quale spengo la pompa
    {
      DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor:" + String(DT.tInletFloor) + " > 35" );
      needPompa_pp = false;
    }
  }
  else
  { // non ho temperatura
    needPompa_pp = false;
  }
  DT.m_log.add( "NeedPompa_pp: [" + String(needPompa_pp) + "]" );

  //////////////////////////////////////////////////////////////////////////////////
  bool needPdc = DT.progWinterPDC && (sala || cucina || bagno);
  if ( needPompa_pp )
  {
    DT.m_log.add(" PDC suspended - Fire enought ");
    needPdc = false;
  }
  DT.m_log.add( "needPdc: [" + String(needPdc) + "]" );

  //////////////////////////////////////////////////////////////////////////////////
  bool needPCamino = false;
  DT.m_log.add("Condizione Pompa Camino: tReturnFireplace " + String(DT.tReturnFireplace) + " - " + "tPufferLow " + String(DT.tPufferLow) + " - " );
  if ( DT.tPufferLow < 45 && DT.tReturnFireplace > 40 && DT.tReturnFireplace > DT.tPufferLow + 5 )
  {
    needPCamino = true;
  }
  DT.m_log.add( "needPCamino: [" + String(needPCamino) + "]" );

  //////////////////////////////////////////////////////////////////////////////////
  bool needPompa_pt = false;
  //decido se accendere sulla lavanderia
  DT.m_log.add("Condizione tPufferLow " +  String(DT.tPufferHi)  + " > 45 ");
  if ( DT.tPufferLow > 45 )
  {
    needPompa_pt = true;
  }
  DT.m_log.add( "NeedPompa_pt: [" + String(needPompa_pt) + "]" );


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
  // accendo pompa
  DT.rPompaPianoPrimo.manualCheck( needPompa_pp );

  // accendo PDC
  DT.rPdc.manualCheck( needPdc );

  // heat
  DT.rPdcHeat.manualCheck( needPdc );

  //pompa
  DT.rPdcPompa.manualCheck( needPdc );

  //night
  DT.rPdcNightMode.manualCheck( needPdc );

  //camino ----------------------------------------------------------------------------------
  DT.rPompaCamino.manualCheck( needPCamino );

  //piano terra
  DT.rPompaPianoTerra.manualCheck( needPompa_pt );
}


