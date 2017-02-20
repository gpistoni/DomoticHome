#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Time.h>

#include "dhwifi.h"
#include "dhconfig.h"
#include "DataTable.h"
#include "functions.h"
#include "googleScript.h"


DHwifi dhWifi;
cDataTable DT;
DHFile     Config;
const int ACT = 2;

//////////////////////////////////////////////////////////////////////////////////
const char* GHost = "script.google.com";
String GScriptId = "/macros/s/AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM/exec?";
const char* GFingerprint = "FD:8C:AC:55:64:BE:30:57:9A:27:53:52:62:E1:CD:26:82:15:A2:DB";

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
  RollingUpdateTerminals( 0 );

  if ( month() >= 9 || month() < 4) DT.progWinterFIRE.set(1);

  UpdateTime();      // update system time

  ScriptValuesLabels();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  digitalWrite(ACT, 1);

  RollingUpdateTerminals( 5 );
  digitalWrite(ACT, 0);
  ScriptValues(60 * 30);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScriptValuesLabels()
{
  GoogleScript GoogleClient(GHost, GFingerprint);
        //String url1 = GScriptId + "sheet=" + "Log" + "&v1=" + "tExternal" + "&v2=" + "tSala" + "&v3=" + "tFloorIN"  + "&v4=" + "tFloorRET" + "&v5=" + "tPufferHi" + "&v6=" + "tPufferLow" + "&v7=" + "tReturnFireplace";
        //DT.m_log.add(url1);
        //GoogleClient.Post(url1);
  String url2 = GScriptId + "sheet=" + "Log" + "&v1=" + "Setup";
  DT.m_log.add(url2);
  GoogleClient.Post(url2);
}

void ScriptValues(int sec)
{
  _CHECK_TIME_;
  if ( DT.tSala > 0 && DT.tInletFloor > 0 && DT.tReturnFloor > 0 && DT.tPufferHi > 0)
  {
    GoogleScript GoogleClient(GHost, GFingerprint);
    String url = GScriptId + "sheet=" + "Temp" + month() + "&v1=" + DT.tExternal + "&v2=" + DT.tSala + "&v3=" + DT.tInletFloor + "&v4=" + DT.tReturnFloor + "&v5=" + DT.tPufferHi + "&v6=" + DT.tPufferLow + "&v7=" + DT.tReturnFireplace;
    DT.m_log.add(url);
    GoogleClient.Post(url);
  }
}

