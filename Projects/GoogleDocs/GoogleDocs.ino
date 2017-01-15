/*
    HTTPS with follow-redirect example
    Created by Sujay S. Phadke, 2016

    Based on the WifiClientSecure example by
    Ivan Grokhotkov
 *  *
    This example is in public domain.
*/
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

// Replace with your network credentials
const char* ssid = "PistoniHome";
const char* password =  "giaco.iren.dario";

const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";
const char *GScriptId = "AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM";

const int httpsPort = 443;

// http://askubuntu.com/questions/156620/how-to-verify-the-ssl-fingerprint-by-command-line-wget-curl/
// echo | openssl s_client -connect script.google.com:443 |& openssl x509 -fingerprint -noout
// www.grc.com doesn't seem to get the right fingerprint
// SHA1 fingerprint of the certificate
//const char* fingerprint = "94 2F 19 F7 A8 B4 5B 09 90 34 36 B2 2A C4 7F 17 06 AC 6A 2E";
//const char* fingerprint = "F0 5C 74 77 3F 6B 25 D7 3B 66 4D 43 2F 7E BC 5B E9 28 86 AD";
//const char* fingerprint2 = "94 64 D8 75 DE 5D 3A E6 3B A7 B6 15 52 72 CC 51 7A BA 2B BE";
//const char* fingerprint = "0D 9A 55 12 4E A0 73 BE DD 1C 02 36 B5 D1 BA 91 66 A6 42 39";
const char* fingerprint = "FD:8C:AC:55:64:BE:30:57:9A:27:53:52:62:E1:CD:26:82:15:A2:DB";

// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?value=Hello";
// Fetch Google Calendar events for 1 week ahead
String url2 = String("/macros/s/") + GScriptId + "/exec?cal";
// Read from Google Spreadsheet
String url3 = String("/macros/s/") + GScriptId + "/exec?read";


String prepareStr(String ssheet, String sdatetime,  String svalue)
{
  return String("/macros/s/") + GScriptId + "/exec?sheet=" + ssheet + "&date=" + sdatetime + "&value=" + svalue;
}

String prepareStr(String ssheet, String sdatetime,  float svalue)
{
  return String("/macros/s/") + GScriptId + "/exec?sheet=" + ssheet + "&date=" + sdatetime + "&value=" + String(svalue);
}
//https://script.google.com/macros/s/AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM/exec?sheet=temp&value=10&date=01/01/2011

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  // flush() is needed to print the above (connecting...) message reliably,
  // in case the wireless connection doesn't go through
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

  // Use HTTPSRedirect class to create TLS connection
  HTTPSRedirect client(httpsPort);
  Serial.print("Connecting to ");
  Serial.println(host);

  bool flag = false;
  for (int i = 0; i < 5; i++)
  {
    int retval = client.connect(host, httpsPort);
    if (retval == 1)
    {
      flag = true;
      break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  Serial.flush();
  if (!flag)
  {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }

  Serial.flush();
  if (client.verify(fingerprint, host))
  {
    Serial.println("Certificate match.");
  }
  else
  {
    Serial.println("Certificate mis-match");
  }

  // Note: setup() must finish within approx. 1s, or the the watchdog timer
  // will reset the chip. Hence don't put too many requests in setup()
  // ref: https://github.com/esp8266/Arduino/issues/34

  //Serial.print("Requesting URL: ");
  //Serial.println(url);

  String str = prepareStr("temp", "01/01/2017 20:20", "1");
  client.printRedir( str, host, googleRedirHost);
  Serial.println("==============================================================================");
}

int i = 1;

void loop()
{
  HTTPSRedirect client(httpsPort);
  
  if (!client.connected())
    client.connect(host, httpsPort);

  String str = prepareStr("temp", "01/01/2017 20:20", i);
  client.printRedir( str, host, googleRedirHost);

  Serial.println(str);
  i++;
  // In my testing on a ESP-01, a delay of less than 1500 resulted
  // in a crash and reboot after about 50 loop runs.
  delay(5000);
}
