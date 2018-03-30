#include <ESP8266WiFi.h>
#include "page1.html.h"

extern WiFiServer httpServer;
extern cDataTable DT;
extern DHFile Config;

String LastPage;

void S_page( WiFiClient &client)
{
  String page;
  page = "HTTP/1.1 200 OK"
         "Content-Type: text/html";
  "Connection: close"
  "Refresh: 5";
  client.println(page);
  client.println(""); //  do not forget this one
  client.println(HTML_page1);
}

void S_value( WiFiClient &client, float val)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/xml");
  client.println("Connection: keep-alive");
  client.println();
  client.print("<?xml version = \"1.0\" ?>");
  client.print("<out>");
  client.print("<value>");
  client.print(val);
  client.print("</value>");
  client.print("</out>");
}

void S_ajax( WiFiClient &client)
{
  Serial.println("HTTP ajax");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/xml");
  client.println("Connection: keep-alive");
  client.println("");
  client.print("<?xml version = \"1.0\" ?>");
  client.print("<data>");
  client.print("<value1>");
  client.print("11");
  client.print("</value1>");
  client.print("<value2>");
  client.print("20");
  client.print("</value2>");
  client.print("<value3>");
  client.print("30");
  client.print("</value3>");
  client.print("</data>");

  Serial.println("HTTP/1.1 200 OK");
  Serial.println("Content-Type: text/xml");
  Serial.println("Connection: keep-alive");
  Serial.println("");
  Serial.print("<?xml version = \"1.0\" ?>");
  Serial.print("<data>");
  Serial.print("<value1>");
  Serial.print("10");
  Serial.print("</value1>");
  Serial.print("<value2>");
  Serial.print("20");
  Serial.print("</value2>");
  Serial.print("<value3>");
  Serial.print("30");
  Serial.print("</value3>");
  Serial.print("</data>");
}


void initHttpServer()
{
  httpServer.begin();

  Serial.println("HTTP server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

bool handleHttpServer()
{
  // Check if a client has connected
  WiFiClient client = httpServer.available();
  if (!client)
  {
    return false;
  }

  // Wait until the client sends some data
  int i = 0;
  if (!client.available())
  {
    // Read the first line of the request
    String readString = client.readStringUntil('\n');
    Serial.print("NEW Request: ");
    Serial.println(readString);

    String line;
    do
    {
      line = client.readStringUntil('\n');
      Serial.println(line);
    }
    while (line.length() > 5);

    // Match the request
    int value = 0;
    if (readString.indexOf("/set?") != -1)
    {
      int idxSET = readString.indexOf("/set?");
      int idxSET2 = readString.indexOf("=", idxSET);

      String name = readString.substring(idxSET + 5, idxSET2);
      String val = readString.substring(idxSET2 + 1, 999);

      DT.setPars( name, val );

      readString = LastPage;
    }
    else if (readString.indexOf("/get?") != -1)
    {
      int idxGET = readString.indexOf("/get?");
      int idxGET2 = readString.indexOf(" ", idxGET);

      String name = readString.substring(idxGET + 5, idxGET2);

      float getval =  DT.getPars( name );

      S_value( client, getval);
    }
    else if (readString.indexOf("/ajax") != -1)
    {
      int idxGET = readString.indexOf("/ajax");
      int idxGET2 = readString.indexOf(" ", idxGET);

      String name = readString.substring(idxGET + 5, idxGET2);

      float getval =  DT.getPars( name );

      S_ajax( client);
    }
    else if (readString.indexOf("/page") != -1)
    {
      S_page( client );
    }
    LastPage = readString;
    return true;
  }
  return false;
}


