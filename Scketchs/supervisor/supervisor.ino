#include <dhwifi.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <HttpClient.h>

#include "DataTable.h"

DHwifi dhWifi;

cDataTable DT;

// A UDP instance to let us send and receive packets over UDP
//WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  IPAddress ip(192, 168, 0, 177);
  IPAddress gateway(192, 168, 0, 254);
  IPAddress subnet(255, 255, 255, 0);

  dhWifi.setup( ip, gateway, subnet );
  delay (1000);

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );           // update system time

  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();

  //Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday

  Alarm.timerRepeat( 3600 * 24, Daily);          // timer for every 24h
  Alarm.timerRepeat( 60,        Hourly);         // timer for every 1h
  Alarm.timerRepeat( 20,        Minute);         // timer for every 60sec

  Alarm.timerRepeat( 60 * 10,   PDC_Manager);     // timer for every 10 minutes
}

void loop()
{
  digitalClockDisplay();
  Alarm.delay(1000);
}

void Daily()
{
  Serial.println("Dayly timer");

  time_t epoch = dhWifi.GetSystemTime();
  if (epoch > 0) setTime( epoch );

}

void Hourly()
{
  Serial.println("Hourly timer");
}

void PDC_Manager()
{
  Serial.println("PDC_Manager timer");
  DT.rPDC = 0;
  DT.rPump = 0;

  //decido se accendere la pdc
  if ( month() >= 6 && month() <= 9) // solo estate
  {
    if ( DT.tExternal > 30 && DT.tInletFloor > 20 )   // t esterne, minima t Acqua raffreddata
    {
      Serial.println("Condizione H1");
      DT.rPDC = 1;
      DT.rCool0_Heat1 = 0;
      DT.rPump = 1;
      DT.rNightmode = 1;
    }
    if ( DT.tInletFloor < DT.tReturnFloor - 1 )
    {
      Serial.println("Condizione H2");
      DT.rPump = 1;
    }
  }

  dhWifi.HttpRequest( String("@set(3,0=") + DT.rPDC  + ")" );
  dhWifi.HttpRequest( String("@set(3,1=") + DT.rCool0_Heat1  + ")" );
  dhWifi.HttpRequest( String("@set(3,2=") + DT.rPump  + ")" );
  dhWifi.HttpRequest( String("@set(3,3=") + DT.rNightmode  + ")" );
}

void Minute()
{
  Serial.println("Minute timer");

  DT.UpdateT3( dhWifi.HttpRequest("@get(3,99)") );
  DT.UpdateT4( dhWifi.HttpRequest("@get(4,99)") );
  DT.UpdateT5( dhWifi.HttpRequest("@get(5,99)") );


}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}
