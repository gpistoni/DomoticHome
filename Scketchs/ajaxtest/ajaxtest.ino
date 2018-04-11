#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <Time.h>
#include <ESPAsyncWebServer.h>

#include "dhwifi.h"
#include "dhconfig.h"
#include "DataTable.h"
#include "functions.h"
#include "httpAjaxServer.h"


DHwifi dhWifi;

cDataTable DT;
DHFile     Config;

//WiFiServer httpServer(80);
AsyncWebServer server(80);

const int ACT = 2;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Serial.println("SETUP");

  pinMode(ACT, OUTPUT);

  IPAddress ip(192, 168, 1, 209);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  String ssid   = "PistoniHome";          // your network SSID (name)
  String pass   = "giaco1iren1dario";     // your network password
  String remote = "192.168.1.200";        // remote server

  dhWifi.setup( ip, gateway, subnet, ssid, pass, remote );

  DT.setup();

  UpdateTime();       // update system time

  ///initHttpServer();   // start web server

  server.on("/html", HTTP_GET, [](AsyncWebServerRequest * request)  {
    request->send(200, "text/html", HTML_page1 );
  });

  server.on("/ajax", HTTP_GET, [](AsyncWebServerRequest * request)  {
    request->send(200, "text/xml", AjaxResponse() );
  });
  
  server.begin();


  RollingUpdateTerminals( 0 );

  if ( month() >= 9 || month() < 4) DT.progWinterFIRE.set(1);

  UpdateTime();      // update system time

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  digitalWrite(ACT, 1);

  RollingUpdateTerminals( 5 );

  digitalWrite(ACT, 0);
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


