#include <ESP8266WiFi.h>
#include "page1.html.h"

#include "ArduinoJson.h"

extern WiFiServer httpServer;
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

JsonObject& prepareResponse(JsonBuffer& jsonBuffer) {
  JsonObject& root = jsonBuffer.createObject();
  root["heap"] = "A";
  root["ssid"] = "123";

  return root;
}

void writeResponse(WiFiClient& client, JsonObject& json) {
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Cache-Control: private");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("");
  client.println();
  json.prettyPrintTo(client);
    
  json.prettyPrintTo(Serial);
}

void S_json(WiFiClient client )
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& json = prepareResponse(jsonBuffer);
  writeResponse(client, json);
}

/*
  String JsonResponse()
  {
  StaticJsonBuffer<500> jsonBuffer;

  JsonObject &root = jsonBuffer.createObject();
  JsonArray &tempValues = root.createNestedArray("temperature");
  tempValues.add(22);
  JsonArray &humiValues = root.createNestedArray("humidity");
  humiValues.add(50);
  JsonArray &dewpValues = root.createNestedArray("dewpoint");
  dewpValues.add(1);
  JsonArray &EsPvValues = root.createNestedArray("systemv");
  EsPvValues.add(200, 3);

  String json;
  root.prettyPrintTo(json);
  return json;
  }
*/
/*
  String JsonResponse()
  {
  printf("Trace: JsonResponse\n");

  StaticJsonBuffer<500> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["heap"] = "A";
  root["ssid"] = "123";

  String json;
  root.prettyPrintTo(json);
  return json;
  }

  String XmlResponse()
  {
  String str;
  str += "<members>";
  str +=   "<id>3422345</id>";
  str +=  "<name>Bill Gates</name>";
  str += "</members>";
  return str;
  }
*/
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
    }
    else if (readString.indexOf("/get?") != -1)
    {
      int idxGET = readString.indexOf("/get?");
      int idxGET2 = readString.indexOf(" ", idxGET);

      String name = readString.substring(idxGET + 5, idxGET2);

      float getval =  DT.getPars( name );

      // S_value( client, getval);
    }
    else if (readString.indexOf("/datatable") != -1)
    {
      int idxGET = readString.indexOf("/datatable");
      int idxGET2 = readString.indexOf(" ", idxGET);

      S_json( client);
    }
    else if (readString.indexOf("/page") != -1)
    {
      //S_page( client );
    }
    return true;
  }
  return false;
}

