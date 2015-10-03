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

const int led = 2;

void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  Serial.begin(115200);
  Serial.println();

  IPAddress ip(192, 168, 0, 201);
  IPAddress gateway(192, 168, 0, 254);
  IPAddress subnet(255, 255, 255, 0);

  dhWifi.setup( ip, gateway, subnet );
  delay (1000);

  DT.setup();

  UpdateTime();      // update system time

  webServer.on("/", handleRoot );
  webServer.on("/log", handleLog );
  webServer.on("/values", handleValues );
  webServer.on("/labels", handleLabels );
  webServer.onNotFound(handleNotFound);
  webServer.begin();
  Serial.println("HTTP server started");

  //Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday

  Alarm.timerRepeat( 3600 * 24, Daily);             // timer for every 24h
  Alarm.timerRepeat( 60 * 60,    Hourly);           // timer for every 1h

  Alarm.timerRepeat( 20,        UpdateAll);         // timer for every 60sec

  Alarm.timerRepeat( 60,        PDC_Manager);             // timer for every 10 minutes
  Alarm.timerRepeat( 61,        winterPP_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 62,        winterPT_Manager);        // timer for every 1 minutes
  Alarm.timerRepeat( 63,        BoilerSanitaria_Manager); // timer for every 1 minutes



  UpdateAll();
  PDC_Manager();
  winterPP_Manager();
  winterPT_Manager();
  BoilerSanitaria_Manager();

}

/**************************************************************************************************/
void loop()
{
  webServer.handleClient();
  digitalWrite(led, 0);
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

void UpdateTime()
{
  Serial.println("UpdateTime");
  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );
}


/**************************************************************************************************/
void UpdateAll()
{
  digitalClockDisplay();
  Serial.println("UpdateAll");

  if (year() < 2000 )
    UpdateTime();

  DT.UpdateT1( dhWifi.HttpRequest( "@get(1,99)") );
  DT.UpdateT3( dhWifi.HttpRequest( "@get(3,99)") );
  DT.UpdateT4( dhWifi.HttpRequest( "@get(4,99)") );
  DT.UpdateT5( dhWifi.HttpRequest( "@get(5,99)") );
}


/**************************************************************************************************/
void PDC_Manager()
{
  digitalClockDisplay();
  Serial.println("PDC_Manager");
  DT.rPdc.set(0);
  DT.rPdcPompa.set(0);

  //decido se accendere la pdc
  if ( month() == 6 ||  month() == 7 || month() == 8 ) // solo estate
  {
    if ( DT.tExternal > 30 && DT.tInletFloor > 20 )   // t esterne, minima t Acqua raffreddata
    {
      Serial.println("Condizione H1");
      DT.rPdc.set(1);
      DT.rPdcCool0_Heat1.set(0);
      DT.rPdcPompa.set(1);
      DT.rPdcNightMode.set(1);
    }
    if ( DT.tInletFloor < DT.tReturnFloor - 1 )
    {
      Serial.println("Condizione H2");
      DT.rPdcPompa.set(1);
    }
  }

  /*
    if ( month() == 9 ) // solo 1/2 stagione
    {
      if ( DT.tExternal > 10 && DT.tPufferHi < 30 )
      {
        Serial.println("Condizione H3");
        DT.rPdc.set(1);;
        DT.rPdcCool0_Heat1.set(1);
        DT.rPdcPompa.set(1);
        DT.rPdcNightMode.set(1);
      }
      if ( DT.tInletFloor < DT.tReturnFloor - 1 )
      {
        Serial.println("Condizione H4");
        DT.rPdcPompa.set(1);
      }
    }
    */

  dhWifi.HttpRequest( DT.rPdc.getS() );
  dhWifi.HttpRequest( DT.rPdcCool0_Heat1.getS() );
  dhWifi.HttpRequest( DT.rPdcPompa.getS() );
  dhWifi.HttpRequest( DT.rPdcNightMode.getS() );
}

/**************************************************************************************************/
void BoilerSanitaria_Manager()
{
  digitalClockDisplay();
  Serial.println("BoilerSanitaria_Manager");
  DT.rBoilerSanitaria.set( 0 );

  //decido se accendere il boiler solo di notte e solo se il camino non funziona
  if ( hour() >= 20 || hour() < 7)
  {
    if ( DT.tReturnFireplace < 30 )
    {
      Serial.println("Condizione B1");
      DT.rBoilerSanitaria.set( 1 );
    }
  }

  dhWifi.HttpRequest( DT.rBoilerSanitaria.getS() );

}

/**************************************************************************************************/
void winterPP_Manager()
{
  digitalClockDisplay();
  Serial.println("winterPP_Manager");
  bool sala = false;
  bool cucina = false;

  //decido se accendere le stanze
  if ( DT.tPufferHi > 25 )
  {
    if ( DT.tSala < 22)
    {
      Serial.println("Condizione S1");
      sala = true;
    }
    if ( DT.tCucina < 21)
    {
      Serial.println("Condizione S2");
      cucina = true;
    }
  }

  bool pompa = sala || cucina;

  // attuatori
  DT.evCameraM1.set(pompa && 0);
  DT.evCameraM2.set(pompa && 0);
  DT.evSala1.set(pompa && sala);
  DT.evSala2.set(pompa && sala);
  DT.evCucina.set(pompa && cucina);
  DT.evCameraS.set(pompa && 0);
  DT.evCameraD1.set(pompa && 0);
  DT.evCameraD2.set(pompa && 0);

  DT.rPompaPianoPrimo.set(pompa);

  dhWifi.HttpRequest( DT.evCameraM1.getS() );
  dhWifi.HttpRequest( DT.evCameraM2.getS() );
  dhWifi.HttpRequest( DT.evSala1.getS() );
  dhWifi.HttpRequest( DT.evSala2.getS() );
  dhWifi.HttpRequest( DT.evCucina.getS() );
  dhWifi.HttpRequest( DT.evCameraS.getS() );
  dhWifi.HttpRequest( DT.evCameraD1.getS() );
  dhWifi.HttpRequest( DT.evCameraD2.getS() );

  dhWifi.HttpRequest( DT.rPompaPianoPrimo.getS() );
}

/**************************************************************************************************/
void winterPT_Manager()
{
  digitalClockDisplay();
  Serial.println("winterPT_Manager");

  bool pompa = false;

  //decido se accendere sulla lavanderia
  if ( DT.tPufferHi > 40 )
  {
     Serial.println("Condizione T1");
     pompa = true;
  }

  DT.rPompaPianoTerra.set(pompa);
  dhWifi.HttpRequest( DT.rPompaPianoTerra.getS() );

}


