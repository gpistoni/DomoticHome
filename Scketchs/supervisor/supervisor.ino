#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <WiFiUdp.h>
#include <Time.h>
#include <TimeAlarms.h>

#include "dhwifi.h"
#include "dhconfig.h"
#include "DataTable.h"
#include "functions.h"
#include "httpServer.h"
#include "httpServer2.h"


DHwifi dhWifi;

cDataTable DT;
DHFile   Config;

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

  UpdateTime();      // update system time

  //  initWebServer();
  initHttpServer();

  Alarm.timerRepeat( 60,        summerPP_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 61,        winterPP_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 62,        winterPT_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 63,        BoilerSanitaria_Manager); // timer for every 1 minutes

  UpdateAll( );
  summerPP_Manager();
  winterPP_Manager();
  winterPT_Manager();
  BoilerSanitaria_Manager();
}

/**************************************************************************************************/
void loop()
{
  digitalWrite(ACT, 1);
  if ( handleHttpServer() )
  {
    // UpdateAll();
  }
  Alarm.delay(100);
  digitalWrite(ACT, 0);
  UpdateAll();
}


/**************************************************************************************************/
void UpdateTime()
{
  Serial.println("UpdateTime");
  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );
}


/**************************************************************************************************/
void UpdateAll()
{
  static unsigned long last = 0;
  if ( millis() - last < 15000 ) return;
  last = millis();

  digitalClockDisplay();
  Serial.println("UpdateAll");

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
void summerPP_Manager()
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

/**************************************************************************************************/
void BoilerSanitaria_Manager()
{
  //digitalWrite(ACT, 0);
  digitalClockDisplay();
  Serial.println("BoilerSanitaria_Manager");

  bool boilerACS = false;

  //decido se accendere il boiler solo di notte e solo se il camino non funziona
  if ( hour() >= 20 || hour() < 7)
  {
    if ( DT.tReturnFireplace < 30 )
    {
      DT.m_log.add("Condizione hour:" + String( hour() ) + " tReturnFireplace < " + String( DT.tReturnFireplace ) );
      boilerACS = true;
    }
  }

  //manual mode
  DT.rBoilerSanitaria.manualCheck( boilerACS );
  DT.rBoilerSanitaria.send(&dhWifi, DT.m_log);
}

/**************************************************************************************************/
void winterPP_Manager()
{
  if ( month() == 6 || month() == 7 || month() == 8 || month() == 9 ) return;  // estate

  //digitalWrite(ACT, 0);
  digitalClockDisplay();
  Serial.println("winterPP_Manager");

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
  if ( hour() > 5 )  
  {
    if ( DT.tSala < DT.tSala.setPoint() )
    {
      DT.m_log.add("Condizione tSala " + String(DT.tSala) + " < " + String(DT.tSala.setPoint()) );
      sala = true;
    }
    if ( DT.tSala < DT.tSala.setPoint() - 1 )
    {
      DT.m_log.add("Condizione tSala2 " + String(DT.tSala) + " << " + String(DT.tSala.setPoint()) );
      sala2 = true;
    }
    if ( DT.tCucina < DT.tCucina.setPoint() )
    {
      DT.m_log.add("Condizione tCucina " + String(DT.tCucina) + " < " + String(DT.tCucina.setPoint()) );
      cucina = true;
    }
    if ( DT.tCameraS < DT.tCameraS.setPoint() )
    {
      DT.m_log.add("Condizione tCameraS " + String(DT.tCameraS) + " < " + String(DT.tCameraS.setPoint()) );
      cameraS = true;
    }
    if ( DT.tCameraD < DT.tCameraD.setPoint() )
    {
      DT.m_log.add("Condizione tCameraD " + String(DT.tCameraD) + " < " + String(DT.tCameraD.setPoint()) );
      cameraD = true;
    }
    if ( DT.tCameraD < DT.tCameraD.setPoint() - 1 )
    {
      DT.m_log.add("Condizione tCameraD2 " + String(DT.tCameraD) + " << " + String(DT.tCameraD.setPoint()) );
      cameraD2 = true;
    }
    if ( DT.tCameraM < DT.tCameraM.setPoint() )
    {
      DT.m_log.add("Condizione tCameraM " + String(DT.tCameraM) + " < " + String(DT.tCameraM.setPoint()) );
      cameraM = true;
    }
    if ( DT.tCameraM < DT.tCameraM.setPoint() - 1 )
    {
      DT.m_log.add("Condizione tCameraM " + String(DT.tCameraM) + " << " + String(DT.tCameraM.setPoint()) );
      cameraM2 = true;
    }
    if ( DT.tBagno < DT.tBagno.setPoint() )
    {
      DT.m_log.add("Condizione tBagno " + String(DT.tBagno) + " < " + String(DT.tBagno.setPoint()) );
      bagno = true;
    }
  }

  bool needCalore = sala || cucina || bagno || cameraS || cameraD || cameraM;

  if ( DT.tPufferLow > 47 )   // emergenza
    {
       DT.m_log.add("Emergenza tPufferLow > 48 ");
      needCalore = sala = cucina = cameraS = cameraD = cameraM = true;
    }

  bool needPompa_pp = false;
  bool needPdc = false;

  //////////////////////////////////////////////////////////////////////////////////
  if ( DT.tInputMixer > 23 || DT.tPufferHi > 23 || DT.tReturnFireplace > 30 )
  {
    DT.m_log.add("Condizione needCalore Puffer");
    needPompa_pp = needCalore;

    if ( ( DT.tInletFloor - DT.tReturnFloor ) <= 2 && random(10) > 2 )  // troppo poco delta
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
  //////////////////////////////////////////////////////////////////////////////////
 // else if ( DT.rPdc.setPoint() == 1  && DT.tExternal > 5  )
 // {
 //   DT.m_log.add("Condizione needCalore PDC tExternal: "  + String(DT.tExternal) );
 //  needPdc = needCalore;  // accendo PDC
 // }
  //////////////////////////////////////////////////////////////////////////////////

  // attuatori
  DT.evCameraM1.set(cameraM);
  DT.evCameraM1.send(&dhWifi, DT.m_log);
  DT.evCameraM2.set(cameraM2);
  DT.evCameraM2.send(&dhWifi, DT.m_log);
  DT.evSala1.set(sala);
  DT.evSala1.send(&dhWifi, DT.m_log);
  DT.evSala2.set(sala2);
  DT.evSala2.send(&dhWifi, DT.m_log);
  DT.evCucina.set(cucina);
  DT.evCucina.send(&dhWifi, DT.m_log);
  DT.evCameraS.set(cameraS);
  DT.evCameraS.send(&dhWifi, DT.m_log);
  DT.evCameraD1.set(cameraD);
  DT.evCameraD1.send(&dhWifi, DT.m_log);
  DT.evCameraD2.set(cameraD2);
  DT.evCameraD2.send(&dhWifi, DT.m_log);


  // comandi semimanuali ---------------------------------------------------------------
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
}

/**************************************************************************************************/
void winterPT_Manager()
{
  digitalClockDisplay();
  Serial.println("winterPT_Manager");

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


