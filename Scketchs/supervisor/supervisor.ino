#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <WiFiUdp.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <HttpClient.h>

//#include <FileIO.h>

#include "dhwifi.h"
#include "DataTable.h"
#include "functions.h"
#include "webServer.h"

DHwifi dhWifi;

cDataTable DT;

ESP8266WebServer webServer(80);

const int ACT = 2;

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

  DT.setup();

  UpdateTime();      // update system time

  initWebserver();

  //Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday

  Alarm.timerRepeat( 3600 * 24, Daily);             // timer for every 24h
  Alarm.timerRepeat( 60 * 60,    Hourly);           // timer for every 1h

  Alarm.timerRepeat( 10,        UpdateAll);         // timer for every 60sec

  Alarm.timerRepeat( 60,        PDC_Manager);             // timer for every 10 minutes
  Alarm.timerRepeat( 61,        winterPP_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 62,        winterPT_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 63,        BoilerSanitaria_Manager); // timer for every 1 minutes

  UpdateAll( );
  PDC_Manager();
  winterPP_Manager();
  winterPT_Manager();
  BoilerSanitaria_Manager();

}

/**************************************************************************************************/
void loop()
{
  webServer.handleClient();
  digitalWrite(ACT, 1);
  Alarm.delay(10);
}

/**************************************************************************************************/
void Daily()
{
  Serial.println("Dayly timer");
  UpdateTime();
}

/**************************************************************************************************/
void Hourly()
{
  Serial.println("Hourly timer");
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
  digitalWrite(ACT, 0);

  static unsigned int i = 0;
  digitalClockDisplay();
  Serial.println("UpdateAll");

  if (year() < 2000 )
    UpdateTime();

  if ( i % 4 == 0 || i == 0 )   DT.UpdateT1( dhWifi.HttpRequest( "@get(1,99)") );
  if ( i % 4 == 1 || i == 0 )   DT.UpdateT3( dhWifi.HttpRequest( "@get(3,99)") );
  if ( i % 4 == 2 || i == 0 )   DT.UpdateT4( dhWifi.HttpRequest( "@get(4,99)") );
  if ( i % 4 == 3 || i == 0 )   DT.UpdateT5( dhWifi.HttpRequest( "@get(5,99)") );

  i++;
}


/**************************************************************************************************/
void PDC_Manager()
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
  digitalWrite(ACT, 0);
  Serial.println("BoilerSanitaria_Manager");

  bool pompa = false;

  //decido se accendere il boiler solo di notte e solo se il camino non funziona
  if ( hour() >= 20 || hour() < 7)
  {
    if ( DT.tReturnFireplace < 30 )
    {
      Serial.println("Condizione B1");
      pompa = true;
    }
  }

  //manual mode
  if ( DT.prBoilerSanitaria )
    pompa = true;

  DT.rBoilerSanitaria.set( pompa );
  DT.rBoilerSanitaria.send(&dhWifi, DT.m_log);
}

/**************************************************************************************************/
void winterPP_Manager()
{
  digitalWrite(ACT, 0);
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

  if ( DT.tSala < DT.ptSala )
  {
    DT.m_log.add("Condizione tSala " + String(DT.tSala) + " < " + String(DT.ptSala) );
    sala = true;
  }
  if ( DT.tSala < DT.ptSala - 1 )
  {
    DT.m_log.add("Condizione tSala2 " + String(DT.tSala) + " << " + String(DT.ptSala) );
    sala2 = true;
  }
  if ( DT.tCucina < DT.ptCucina )
  {
    DT.m_log.add("Condizione tCucina " + String(DT.tCucina) + " < " + String(DT.ptCucina) );
    cucina = true;
  }
  if ( DT.tCameraS < DT.ptCameraS )
  {
    DT.m_log.add("Condizione tCameraS " + String(DT.tCameraS) + " < " + String(DT.ptCameraS) );
    cameraS = true;
  }
  if ( DT.tCameraD < DT.ptCameraD )
  {
    DT.m_log.add("Condizione tCameraD " + String(DT.tCameraD) + " < " + String(DT.ptCameraD) );
    cameraD = true;
  }
  if ( DT.tCameraD < DT.ptCameraD - 1 )
  {
    DT.m_log.add("Condizione tCameraD2 " + String(DT.tCameraD) + " << " + String(DT.ptCameraD) );
    cameraD2 = true;
  }
  if ( DT.tCameraM < DT.ptCameraM )
  {
    DT.m_log.add("Condizione tCameraM " + String(DT.tCameraM) + " < " + String(DT.ptCameraM) );
    cameraM = true;
  }
  if ( DT.tCameraM < DT.ptCameraM - 1 )
  {
    DT.m_log.add("Condizione tCameraM " + String(DT.tCameraM) + " << " + String(DT.ptCameraM) );
    cameraM2 = true;
  }
  if ( DT.tBagno < DT.ptBagno )
  {
    DT.m_log.add("Condizione tBagno " + String(DT.tBagno) + " < " + String(DT.ptBagno) );
    bagno = true;
  }
  if ( hour() >= 19 || hour() < 8 )
  {
    DT.m_log.add("Condizione bagno hour " + String( hour() ) );
    bagno = true;
  }

  bool needCalore = sala || cucina || bagno || cameraS || cameraD || cameraM;

  bool needPompa_pp = false;
  bool needPdc = false;

  if ( DT.tPufferHi > 25 )
  {
    DT.m_log.add("Condizione needCalore Puffer");
    needPompa_pp = needCalore;
  }
  else if ( DT.prPdc && DT.tExternal > 10  )
  {
    DT.m_log.add("Condizione needCalore PDC tExternal: "  + String(DT.tExternal) );
    needPdc = needCalore;  // accendo PDC
  }

  needPdc = true;

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
  DT.evCameraD2.send(&dhWifi, DT.m_log);;

  // accendo pompa
  DT.rPompaPianoPrimo.set( needPompa_pp );
  DT.rPompaPianoPrimo.send(&dhWifi, DT.m_log );

  // accendo PDC
  DT.rPdc.set( needPdc );
  DT.rPdc.send(&dhWifi, DT.m_log );
  DT.rPdcCool0_Heat1.set( needPdc );
  DT.rPdcCool0_Heat1.send(&dhWifi, DT.m_log );
  DT.rPdcPompa.set( needPdc );
  DT.rPdcPompa.send(&dhWifi, DT.m_log );
  DT.rPdcNightMode.set( needPdc );
  DT.rPdcNightMode.send(&dhWifi, DT.m_log );
}

/**************************************************************************************************/
void winterPT_Manager()
{
  digitalWrite(ACT, 0);
  Serial.println("winterPT_Manager");

  bool pompa = false;

  //decido se accendere sulla lavanderia
  if ( DT.tPufferHi > 40 )
  {
    DT.m_log.add("Condizione tPufferHi:" +  String(DT.tPufferHi) );
    pompa = true;
  }

  //manual mode
  if ( DT.prPompaPianoTerra )
    pompa = true;

  DT.rPompaPianoTerra.set(pompa);
  DT.rPompaPianoTerra.send(&dhWifi,  DT.m_log);
}


