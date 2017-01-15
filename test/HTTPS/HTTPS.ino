/*
    HTTP over TLS (HTTPS) example sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.

    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/

#include <ESP8266WiFi.h>
#include "HttpsClient.h"
#include <Time.h>


const char* ssid = "PistoniHome";
const char* password =  "giaco.iren.dario";

const char* host = "script.google.com";
const int httpsPort = 443;

const char *GScriptId = "AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM";


String prepareStr(String ssheet, String sdatetime,  float svalue)
{
  return String("/macros/s/") + GScriptId + "/exec?sheet=" + ssheet + "&date=" + sdatetime + "&value=" + String(svalue);
}

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "FD:8C:AC:55:64:BE:30:57:9A:27:53:52:62:E1:CD:26:82:15:A2:DB";


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection

  //client.Connect(host, httpsPort, fingerprint);
  //String url = "/macros/s/AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM/exec?sheet=temp&value=111&date=01/01/2011";
  //client.Post(url);
}

int i = 1;

void loop()
{
  i++;
  HTTPSCleint client;
  client.Connect(host, httpsPort, fingerprint);
  String url = String("/macros/s/AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM/exec?sheet=temp") + "&value=" + i + "&date=" + day() + "/" + month() + "/" + year() + "&time=" + hour() + ":" + minute() + ":" + second();
  client.Post(url);
  delay(10000);
}
