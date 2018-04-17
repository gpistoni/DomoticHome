// Now using ESP8266.....
// Sample Arduino Json Web Server
// Created by Benoit Blanchon.
// Heavily inspired by "Web Server" from David A. Mellis and Tom Igoe


#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

// needed to avoid link error on ram check
//extern "C"
//{
//#include "user_interface.h"
//}
//ADC_MODE(ADC_VCC);


WiFiServer server(80);

String ssid   = "PistoniHome";          // your network SSID (name)
String pass   = "giaco1iren1dario";     // your network password

float pfDew, pfHum, pfTemp, pfVcc;

bool readRequest(WiFiClient& client)
{
  bool currentLineIsBlank = true;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (c == '\n' && currentLineIsBlank) {
        return true;
      } else if (c == '\n') {
        currentLineIsBlank = true;
      } else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
  return false;
}

JsonObject& prepareResponse(JsonBuffer& jsonBuffer) {
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& tempValues = root.createNestedArray("temperature");
  tempValues.add(pfTemp);
  JsonArray& humiValues = root.createNestedArray("humidity");
  humiValues.add(pfHum);
  JsonArray& dewpValues = root.createNestedArray("dewpoint");
  dewpValues.add(pfDew);
  JsonArray& EsPvValues = root.createNestedArray("Systemv");
  EsPvValues.add(pfVcc / 1000, 3);
  return root;
}

void writeResponse(WiFiClient& client, JsonObject& json) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();

  json.prettyPrintTo(client);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("SETUP");

  delay(2000);
  // inital connect
  WiFi.mode(WIFI_STA);
  delay(1000);
  // Connect to WiFi network
  WiFi.begin(ssid.c_str(), pass.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(ssid + " not Linked.");
  }
  Serial.println(ssid + " Linked.");
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (client) {
    bool success = readRequest(client);
    if (success) {
      delay(1000);
      pfTemp = 22;
      pfHum = 55;
      float a = 17.67;
      float b = 243.5;
      float alpha = (a * pfTemp) / (b + pfTemp) + log(pfHum / 100);
      pfDew = (b * alpha) / (a - alpha);
      delay(500);
      pfVcc = ESP.getVcc();

      StaticJsonBuffer<500> jsonBuffer;
      JsonObject& json = prepareResponse(jsonBuffer);
      writeResponse(client, json);
    }
    delay(1);
    client.stop();
  }
}

