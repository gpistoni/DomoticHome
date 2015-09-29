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

ESP8266WebServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  IPAddress ip(192, 168, 0, 201);
  IPAddress gateway(192, 168, 0, 254);
  IPAddress subnet(255, 255, 255, 0);

  dhWifi.setup( ip, gateway, subnet );
  delay (1000);

  DT.setup();

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );           // update system time


  server.on("/", handleRoot);
  server.on("/log", handleLog);
  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  //Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday

  Alarm.timerRepeat( 3600 * 24, Daily);          // timer for every 24h
  Alarm.timerRepeat( 60,        Hourly);         // timer for every 1h
  Alarm.timerRepeat( 20,        Minute);         // timer for every 60sec

  Alarm.timerRepeat( 60 * 10,   PDC_Manager);             // timer for every 10 minutes
  Alarm.timerRepeat( 60,        BoilerSanitaria_Manager); // timer for every 1 minutes
}

/**************************************************************************************************/
void loop()
{  
  server.handleClient();
  Alarm.delay(100);
}

/**************************************************************************************************/
void Daily()
{
  Serial.println("Dayly timer");

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );

}

/**************************************************************************************************/
void Hourly()
{
  Serial.println("Hourly timer");
}

/**************************************************************************************************/
void Minute()
{
  digitalClockDisplay();
  Serial.println("Minute timer");

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

  dhWifi.HttpRequest( DT.rPdc.getS() );             Serial.println(  DT.rPdc.getS() );
  dhWifi.HttpRequest( DT.rPdcCool0_Heat1.getS() );  Serial.println(  DT.rPdcCool0_Heat1.getS() );
  dhWifi.HttpRequest( DT.rPdcPompa.getS() );        Serial.println(  DT.rPdcPompa.getS() );
  dhWifi.HttpRequest( DT.rPdcNightMode.getS() );    Serial.println(  DT.rPdcNightMode.getS() );
}

/**************************************************************************************************/
void BoilerSanitaria_Manager()
{
  digitalClockDisplay();
  Serial.println("BoilerSanitaria_Manager");
  DT.rBoilerSanitaria.set( 0 );
 
  //decido se accendere il boiler solo di notte
  if ( hour() >= 20 || hour() < 7)
  {
    Serial.println("Condizione B1");
    DT.rBoilerSanitaria.set( 1 );
  }

  dhWifi.HttpRequest( DT.rBoilerSanitaria.getS() );
  Serial.println(  DT.rBoilerSanitaria.getS() );
}




