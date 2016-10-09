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

  //  initWebServer();
  initHttpServer();

  UpdateAll( );

  DT.progBoilerSanitaria == 1;
  if ( month() >= 9 || month() < 4) DT.progWinterFIRE == 1;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  digitalWrite(ACT, 1);
  if ( handleHttpServer() )
  {
    BoilerSanitaria_Manager( 20 );
    Summer_Manager( 20 );
    Winter_Manager( 5 );
    return;
  }

  delay (100);
  digitalWrite(ACT, 0);
  UpdateAll();

  DT.progBoilerSanitaria.manualCheck( false );
  DT.progSummerAC.manualCheck( false );
  DT.progWinterFIRE.manualCheck( false );
  DT.progWinterPDC.manualCheck( false );
  DT.prog4.manualCheck( false );
  DT.prog5.manualCheck( false );

  if (DT.progBoilerSanitaria)   BoilerSanitaria_Manager( 600 );
  if (DT.progSummerAC)          Summer_Manager( 600 );
  if (DT.progWinterFIRE || DT.progWinterPDC )        Winter_Manager( 600 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateTime()
{
  DT.m_log.add("-- UpdateTime --");

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateAll()
{
  static unsigned long last = 0;
  if ( millis() - last < 15000 ) return;
  last = millis();

  //DT.m_log.add("-- UpdateAll --");

  if (year() < 2000 )
    UpdateTime();

  static unsigned int i = 0;

  if ( i % 4 == 0 || i == 0 )   DT.UpdateT1( dhWifi.HttpRequest( "@get(1,99)") );
  if ( i % 4 == 1 || i == 0 )   DT.UpdateT3( dhWifi.HttpRequest( "@get(3,99)") );
  if ( i % 4 == 2 || i == 0 )   DT.UpdateT4( dhWifi.HttpRequest( "@get(4,99)") );
  if ( i % 4 == 3 || i == 0 )   DT.UpdateT5( dhWifi.HttpRequest( "@get(5,99)") );

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
  if ( hour() < 7 &&  DT.tReturnFireplace < 30  + boilerACS * 2 ) //isteresi
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
  DT.rBoilerSanitaria.send( &dhWifi, DT.m_log);
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
  else
  {
    summerAC = false;
  }
  /**************************************************************************************************/

  DT.m_log.add("summerAC [" +  String(summerAC) + "] tExternal: " + String( DT.tExternal ) + " tSala: " + String( DT.tSala ) + " tReturnFloor: " + String( DT.tReturnFloor ));

  // attuatori
  DT.evCameraM1.set(summerAC);   DT.evCameraM1.send(&dhWifi, DT.m_log);
  DT.evSala1.set(summerAC);      DT.evSala1.send(&dhWifi, DT.m_log);
  DT.evSala2.set(summerAC);      DT.evSala2.send(&dhWifi, DT.m_log);
  DT.evCucina.set(summerAC);     DT.evCucina.send(&dhWifi, DT.m_log);
  DT.evCameraS.set(summerAC);    DT.evCameraS.send(&dhWifi, DT.m_log);
  DT.evCameraD1.set(summerAC);   DT.evCameraD1.send(&dhWifi, DT.m_log);

  // accendo PDC
  DT.rPdc.manualCheck( summerAC );           DT.rPdc.send(&dhWifi, DT.m_log );
  DT.rPdcHeat.set( false );                  DT.rPdcHeat.send(&dhWifi, DT.m_log );
  DT.rPdcPompa.set( summerAC );              DT.rPdcPompa.send(&dhWifi, DT.m_log );
  DT.rPdcNightMode.manualCheck( true );      DT.rPdcNightMode.send(&dhWifi, DT.m_log );
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
  bool needCalore = ( sala || cucina || bagno || cameraS || cameraD || cameraM );
  if ( DT.tPufferLow > 48 )   // emergenza
  {
    DT.m_log.add("Emergenza tPufferLow > 48 ");
    needCalore = sala = cucina = cameraS = cameraD = cameraM = true;
  }

  //////////////////////////////////////////////////////////////////////////////////
  bool needPompa_pp = false;
  if ( DT.tInputMixer > 23 || DT.tPufferHi > 23 || DT.tReturnFireplace > 30 )
  {
    DT.m_log.add("Condizione needCalore Puffer");
    needPompa_pp = needCalore;

    /*
      if ( ( DT.tInletFloor - DT.tReturnFloor ) <= 2 && DT.tInletFloor > 23 )  // troppo poco delta
      {
      DT.m_log.add("Stop Pompa: Delta temp insufficiente");
      DT.m_log.add("DT.tInletFloor " + String(DT.tInletFloor) + " - " + "DT.tReturnFloor " + String(DT.tReturnFloor) + " - " );
      needPompa_pp = false;
      }
    */
    if ( DT.tInletFloor > 35 || DT.tReturnFloor > 29  )  //35 è la sicurezza, 29 la t massima dopo al quale spengo la pompa
    {
      DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto");
      DT.m_log.add("DT.tInletFloor " + String(DT.tInletFloor) + " - " + "DT.tReturnFloor " + String(DT.tReturnFloor) + " - " );
      needPompa_pp = false;
    }
  }
  DT.m_log.add( "needPompa_pp:" + needPompa_pp );


  //////////////////////////////////////////////////////////////////////////////////
  bool needPdc = DT.progWinterPDC && (sala || cucina || bagno);
  if ( needPompa_pp )
  {
    DT.m_log.add(" PDC suspended - Fire enought ");
    needPdc = false;
  }
  DT.m_log.add( "needPdc:" + needPdc );

  //////////////////////////////////////////////////////////////////////////////////
  bool needPCamino = false;
  if ( DT.tPufferLow < 45 && DT.tReturnFireplace > DT.tPufferLow + 4 )
  {
    DT.m_log.add("Condizione Pompa Camino: DT.tReturnFireplace " + String(DT.tReturnFireplace) + " - " + "DT.tPufferLow " + String(DT.tPufferLow) + " - " );
    needPCamino = true;
  }
  DT.m_log.add( "needPCamino:" + needPCamino );

  //////////////////////////////////////////////////////////////////////////////////
  bool needPompa_pt = false;
  //decido se accendere sulla lavanderia
  if ( DT.tPufferLow > 45 )
  {
    DT.m_log.add("Condizione tPufferLow " +  String(DT.tPufferHi)  + " > 45 ");
    needPompa_pt = true;
  }
  DT.m_log.add( "needPompa_pt:" + needPompa_pt );

  cameraM   = cameraM && ( needPompa_pp );
  cameraM2  = cameraM2 && ( needPompa_pp );
  sala      = sala && ( needPompa_pp || needPdc );
  sala2     = sala2 && ( needPompa_pp || needPdc );
  cucina    = cucina && ( needPompa_pp || needPdc );
  cameraS   = cameraS && ( needPompa_pp || needPdc );
  cameraD   = cameraD && ( needPompa_pp || needPdc );
  cameraD2  = cameraD2 && ( needPompa_pp );

  // attuatori -----------------------------------------------------------------------
  DT.evCameraM1.set(cameraM);   DT.evCameraM1.send(&dhWifi, DT.m_log);
  DT.evCameraM2.set(cameraM2);  DT.evCameraM2.send(&dhWifi, DT.m_log);
  DT.evSala1.set(sala);         DT.evSala1.send(&dhWifi, DT.m_log);
  DT.evSala2.set(sala2);        DT.evSala2.send(&dhWifi, DT.m_log);
  DT.evCucina.set(cucina);      DT.evCucina.send(&dhWifi, DT.m_log);
  DT.evCameraS.set(cameraS);    DT.evCameraS.send(&dhWifi, DT.m_log);
  DT.evCameraD1.set(cameraD);   DT.evCameraD1.send(&dhWifi, DT.m_log);
  DT.evCameraD2.set(cameraD2);  DT.evCameraD2.send(&dhWifi, DT.m_log);

  // comandi semimanuali centrale -----------------------------------------------------
  // accendo pompa
  DT.rPompaPianoPrimo.manualCheck( needPompa_pp );
  DT.rPompaPianoPrimo.send(&dhWifi, DT.m_log );

  // accendo PDC
  DT.rPdc.manualCheck( needPdc );
  DT.rPdc.send(&dhWifi, DT.m_log );

  // heat
  DT.rPdcHeat.manualCheck( needPdc );
  DT.rPdcHeat.send(&dhWifi, DT.m_log );

  //pompa
  DT.rPdcPompa.manualCheck( needPdc );
  DT.rPdcPompa.send(&dhWifi, DT.m_log );

  //night
  DT.rPdcNightMode.manualCheck( needPdc );
  DT.rPdcNightMode.send(&dhWifi, DT.m_log );

  //camino ----------------------------------------------------------------------------------
  DT.rPompaCamino.manualCheck( needPCamino );
  DT.rPompaCamino.send(&dhWifi, DT.m_log );

  //piano terra
  DT.rPompaPianoTerra.manualCheck(needPompa_pt);
  DT.rPompaPianoTerra.send(&dhWifi,  DT.m_log);
}


