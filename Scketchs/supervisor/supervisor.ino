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

void Daily();
void UpdateTime();
void UpdateAll();
void summerPP_Manager();
void winterPP_Manager();
void winterPT_Manager();
void BoilerSanitaria_Manager();

void setup()
{
  pinMode(ACT, OUTPUT);
  digitalWrite(ACT, 0);

  Serial.begin(115200);
  Serial.println();

  IPAddress ip(192, 168, 0, 201);
  IPAddress gateway(192, 168, 0, 254);
  IPAddress subnet(255, 255, 255, 0);

  dhWifi.setup( ip, gateway, subnet );
  delay (1000);

  Config.LoadFile();
  DT.setup();

  Config.ReadValue("T1");
  Config.SaveFile();

  UpdateTime();      // update system time

  //  initWebServer();
  initHttpServer();

  UpdateAll( );

  DT.progBoilerSanitaria == 1;
  
}

/**************************************************************************************************/
void loop()
{
  digitalWrite(ACT, 1);
  if ( handleHttpServer() )
  {
    summerPP_Manager(5);
    //winterPP_Manager(5);
    //winterPDC_Manager( 5 );
    
    winterPT_Manager(5);
  }
  UpdateAll();
  digitalWrite(ACT, 0);

  summerPP_Manager( 60 );
  
  //winterPP_Manager( 60 );
  //winterPDC_Manager( 60 );
  
  winterPT_Manager( 60 );

  DT.progBoilerSanitaria.manualCheck( false );
  DT.progSummerEco.manualCheck( false );
    
  if (DT.progBoilerSanitaria) BoilerSanitaria_Manager( 600 );
  if (DT.progSummerEco)       SummerEco_Manager( 10 );   
}


/**************************************************************************************************/
void UpdateTime()
{
  DT.m_log.add("-- UpdateTime --");

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );
}


/**************************************************************************************************/
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


/**************************************************************************************************/
void summerPP_Manager(int sec)
{
  static unsigned long last = 0;
  if ( millis() - last < sec * 1000 ) return;
  last = millis();

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

/**************************************************************************************************/
void BoilerSanitaria_Manager(int sec)
{
  static unsigned long last = 0;
  if ( millis() - last < sec * 1000 ) return;
  last = millis();

  digitalClockDisplay();

  bool boilerACS = false;  
 /**************************************************************************************************/
 {
    //decido se accendere il boiler solo di notte e solo se il camino non funziona
    if ( hour() < 7 &&  DT.tReturnFireplace < 30 )
    {
      boilerACS = true;
    }
  }
/**************************************************************************************************/
 
  DT.m_log.add("Boiler ACS :" + String(boilerACS) + "  hour:" + String( hour() ) + " tReturnFireplace: " + String( DT.tReturnFireplace ) );
   
  // boiler
  DT.rBoilerSanitaria.manualCheck( boilerACS );
  DT.rBoilerSanitaria.send( &dhWifi, DT.m_log);
}

/******************************************************************************************************************************************************************/
void SummerEco_Manager(int sec)
{
  static unsigned long last = 0;
  if ( millis() - last < sec * 1000 ) return;
  last = millis();

  digitalClockDisplay();

  bool summerEco = false;

/**************************************************************************************************/
  {
    // decido se accendere le pompe
    if ( DT.tPufferHi < 24  && DT.tExternal > 24 )
    {
      summerEco = true;
    }
  } 
/**************************************************************************************************/

  DT.m_log.add("SummerEco:" +  String(summerEco) + " tPufferHi: " + String( DT.tPufferHi ) + " tExternal: " + String( DT.tExternal ));
      
  // attuatori
  DT.evCameraM1.set(summerEco);   DT.evCameraM1.send(&dhWifi, DT.m_log);
  DT.evSala1.set(summerEco);      DT.evSala1.send(&dhWifi, DT.m_log);
  DT.evCucina.set(summerEco);     DT.evCucina.send(&dhWifi, DT.m_log);
  DT.evCameraS.set(summerEco);    DT.evCameraS.send(&dhWifi, DT.m_log);
  DT.evCameraD1.set(summerEco);   DT.evCameraD1.send(&dhWifi, DT.m_log);

  // accendo pompa
  DT.rPompaPianoPrimo.manualCheck( summerEco );  DT.rPompaPianoPrimo.send(&dhWifi, DT.m_log );
 
}

/******************************************************************************************************************************************************************/
void winterPP_Manager(int sec)
{
  static unsigned long last = 0;
  if ( millis() - last < sec * 1000 ) return;
  last = millis();

  if ( month() == 6 || month() == 7 || month() == 8 || month() == 9 ) return;  // estate

  digitalWrite(ACT, 0);
  digitalClockDisplay();
  //DT.m_log.add("-- winterPP_Manager --");

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


  bool needCalore = sala || cucina || bagno || cameraS || cameraD || cameraM;

  if ( DT.tPufferLow > 48 )   // emergenza
  {
    DT.m_log.add("Emergenza tPufferLow > 48 ");
    needCalore = sala = cucina = cameraS = cameraD = cameraM = true;
  }

  bool needPompa_pp = false;

  //////////////////////////////////////////////////////////////////////////////////
  if ( DT.tInputMixer > 23 || DT.tPufferHi > 23 || DT.tReturnFireplace > 30 )
  {
    DT.m_log.add("Condizione needCalore Puffer");
    needPompa_pp = needCalore;

    if ( ( DT.tInletFloor - DT.tReturnFloor ) <= 2 && DT.tInletFloor > 23 )  // troppo poco delta
    {
      DT.m_log.add("Stop Pompa: Delta temp insufficiente");
      DT.m_log.add("DT.tInletFloor " + String(DT.tInletFloor) + " - " + "DT.tReturnFloor " + String(DT.tReturnFloor) + " - " );
      needPompa_pp = false;
    }
    if ( DT.tInletFloor > 35 || DT.tReturnFloor > 29  )  //35 è la sicurezza, 29 la t massima dopo al quale spengo la pompa
    {
      DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto");
      DT.m_log.add("DT.tInletFloor " + String(DT.tInletFloor) + " - " + "DT.tReturnFloor " + String(DT.tReturnFloor) + " - " );
      needPompa_pp = false;
    }
  }

  bool needPCamino = false;
  //////////////////////////////////////////////////////////////////////////////////
  if ( DT.tPufferLow < 45 && DT.tReturnFireplace > DT.tPufferLow + 4 )
  {
    DT.m_log.add("Condizione Pompa Camino: DT.tReturnFireplace " + String(DT.tReturnFireplace) + " - " + "DT.tPufferLow " + String(DT.tPufferLow) + " - " );
    needPCamino = true;
  }

  // attuatori
  DT.evCameraM1.set(cameraM && needPompa_pp);   DT.evCameraM1.send(&dhWifi, DT.m_log);
  DT.evCameraM2.set(cameraM2 && needPompa_pp);  DT.evCameraM2.send(&dhWifi, DT.m_log);
  DT.evSala1.set(sala && needPompa_pp);         DT.evSala1.send(&dhWifi, DT.m_log);
  DT.evSala2.set(sala2 && needPompa_pp);        DT.evSala2.send(&dhWifi, DT.m_log);
  DT.evCucina.set(cucina && needPompa_pp);      DT.evCucina.send(&dhWifi, DT.m_log);
  DT.evCameraS.set(cameraS && needPompa_pp);    DT.evCameraS.send(&dhWifi, DT.m_log);
  DT.evCameraD1.set(cameraD && needPompa_pp);   DT.evCameraD1.send(&dhWifi, DT.m_log);
  DT.evCameraD2.set(cameraD2 && needPompa_pp);  DT.evCameraD2.send(&dhWifi, DT.m_log);


  // comandi semimanuali ---------------------------------------------------------------
  // accendo pompa
  DT.rPompaPianoPrimo.manualCheck( needPompa_pp );
  DT.rPompaPianoPrimo.send(&dhWifi, DT.m_log );

  // accendo PDC
  DT.rPdc.manualCheck( false );
  DT.rPdc.send(&dhWifi, DT.m_log );

  // heat
  DT.rPdcHeat.manualCheck( false );
  DT.rPdcHeat.send(&dhWifi, DT.m_log );

  //pompa
  DT.rPdcPompa.manualCheck( false );
  DT.rPdcPompa.send(&dhWifi, DT.m_log );

  //night
  DT.rPdcNightMode.manualCheck( false );
  DT.rPdcNightMode.send(&dhWifi, DT.m_log );

  //camino
  DT.rPompaCamino.manualCheck( needPCamino );
  DT.rPompaCamino.send(&dhWifi, DT.m_log );
}

/**************************************************************************************************/
void winterPDC_Manager(int sec)
{
  static unsigned long last = 0;
  if ( millis() - last < sec * 1000 ) return;
  last = millis();

  digitalWrite(ACT, 0);
  digitalClockDisplay();
  DT.m_log.add("-- winterPDC_Manager --");

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
//  if ( DT.tCucina < DT.tCucina.setPoint() )
//  {
//    str += " tCucina " + String(DT.tCucina) + " < " + String(DT.tCucina.setPoint());
//    cucina = true;
//  }
//  if ( !sala2 && DT.tCameraS < DT.tCameraS.setPoint() )
//  {
//    str += " tCameraS " + String(DT.tCameraS) + " < " + String(DT.tCameraS.setPoint());
//    cameraS = true;
//  }
//  if ( !sala2 && DT.tCameraD < DT.tCameraD.setPoint() )
//  {
//    str += " tCameraD " + String(DT.tCameraD) + " < " + String(DT.tCameraD.setPoint());
//    cameraD = true;
//  }
//  if ( !sala2 && DT.tCameraD < DT.tCameraD.setPoint() - 1 )
//  {
//    str += " tCameraD2 " + String(DT.tCameraD) + " << " + String(DT.tCameraD.setPoint());
//    cameraD2 = true;
//  }
//  if ( !sala2 && DT.tCameraM < DT.tCameraM.setPoint() )
//  {
//    str += " tCameraM " + String(DT.tCameraM) + " < " + String(DT.tCameraM.setPoint());
//    cameraM = true;
//  }
//  if ( !sala2 && DT.tCameraM < DT.tCameraM.setPoint() - 1 )
//  {
//    str += " tCameraM " + String(DT.tCameraM) + " << " + String(DT.tCameraM.setPoint()) ;
//    cameraM2 = true;
//  }
  if ( DT.tBagno < DT.tBagno.setPoint() )
  {
    str += " tBagno " + String(DT.tBagno) + " < " + String(DT.tBagno.setPoint());
    bagno = true;
  }
  DT.m_log.add(str);

  bool needPdc = sala || cucina || bagno || cameraS || cameraD || cameraM;

  if ( DT.tPufferHi > 20 )   // non ho bisogno della pdc, grazie
  {
    DT.m_log.add("Evito PDC tPufferHi > 20 ");
    needPdc = false;
  }

  // attuatori
  DT.evCameraM1.set(cameraM && needPdc);   DT.evCameraM1.send(&dhWifi, DT.m_log);
  DT.evCameraM2.set(cameraM2 && needPdc);  DT.evCameraM2.send(&dhWifi, DT.m_log);
  DT.evSala1.set(sala && needPdc);         DT.evSala1.send(&dhWifi, DT.m_log);
  DT.evSala2.set(sala2 && needPdc);        DT.evSala2.send(&dhWifi, DT.m_log);
  DT.evCucina.set(cucina && needPdc);      DT.evCucina.send(&dhWifi, DT.m_log);
  DT.evCameraS.set(cameraS && needPdc);    DT.evCameraS.send(&dhWifi, DT.m_log);
  DT.evCameraD1.set(cameraD && needPdc);   DT.evCameraD1.send(&dhWifi, DT.m_log);
  DT.evCameraD2.set(cameraD2 && needPdc);  DT.evCameraD2.send(&dhWifi, DT.m_log);

  // comandi semimanuali ---------------------------------------------------------------
  // accendo pompa
  DT.rPompaPianoPrimo.manualCheck( 0 );
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
}

/**************************************************************************************************/
void winterPT_Manager(int sec)
{
  static unsigned long last = 0;
  if ( millis() - last < sec * 1000 ) return;
  last = millis();

  digitalClockDisplay();
  //DT.m_log.add("-- winterPT_Manager --");

  bool needPompa_pt = false;

  //decido se accendere sulla lavanderia
  if ( DT.tPufferLow > 47 )
  {
    DT.m_log.add("Condizione tPufferHi:" +  String(DT.tPufferHi) );
    needPompa_pt = true;
  }

  //piano terra
  DT.rPompaPianoTerra.manualCheck(needPompa_pt);
  DT.rPompaPianoTerra.send(&dhWifi,  DT.m_log);
}


