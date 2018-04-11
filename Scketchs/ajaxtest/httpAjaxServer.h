#include <ESP8266WiFi.h>
#include "page1.html.h"

//extern WiFiServer httpServer;
extern cDataTable DT;
extern DHFile Config;

String AjaxResponse()
{
  String str;
  str += "<?xml version = \"1.0\" ?>";
  str += "<data>";
  str += "<struct>";
  str += DT.printSTRUCT();
  str += "</struct>";
  str += "<values>";
  str += DT.printXML();
  str += "</values>";
  str += "</data>";
  return str;
}


/*
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
*/

