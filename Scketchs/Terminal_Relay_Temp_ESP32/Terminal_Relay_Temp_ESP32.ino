#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include "CDallasProbe.h"
#include "CRelay.h"

//**************************************************
#define NODE_22
//**************************************************
// Nodi utilizzati:
//**************************************************
// 21   ESP32   Relay                         Luci esterne
// 22   ESP32   Relay(8) + InputTemps(8)      Gestione Caldaie
//**************************************************


WebServer server(80);

// Setup IP
#ifdef NODE_21
IPAddress local_IP(192, 168, 1, 21);
#endif
#ifdef NODE_22
IPAddress local_IP(192, 168, 1, 22);
#endif
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

//Libreria DH
#include <dhlibrary.h>


std::vector<CRelay>  Relays = {
#if ( defined NODE_21 || defined NODE_22)
  CRelay(18),
  CRelay(17),
  CRelay(16),
  CRelay(4),
  CRelay(19),
  CRelay(21),
  CRelay(22),
  CRelay(23)
#endif
};

std::vector<CDallasProbe>  Probes = {
#if ( defined NODE_22 )
  CDallasProbe(14),
  //CDallasProbe(27),
  //CDallasProbe(26),
  //CDallasProbe(25),
  CDallasProbe(35),
  CDallasProbe(34),
  CDallasProbe(39),
  CDallasProbe(36)
#endif
};


// TIMING
void handleRoot();
void handleNotFound();

void setup(void)
{
  setupWIFI();

  // Init Relaay Probes
  for (uint8_t i = 0; i < Relays.size(); i++)  Relays[i].setup();   // 8 rele'
  for (uint8_t i = 0; i < Probes.size(); i++)  Probes[i].setup();   // 8 temperature input

  //risponditore
  server.on("/", HTTP_GET, handleRoot);

  //risponditore
  server.on("/test", HTTP_GET, []() {
    server.send(200, "text/plain", "this works as well");
  });

  //risponditore not found
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Server ready..");
}

unsigned long last_read = millis();
unsigned long last_io = millis();
unsigned long ledValue = 0;

void loop(void)
{
  server.handleClient();

  //Watchdog restart
  if ( (millis() - last_io) > (1000 * 60 * 60) ) // 60 minutes
  {
    Serial.print(millis() / 1000.0);
    Serial.println("RESET INACTIVITY");
    resetFunc();
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(millis() / 1000.0);
    Serial.println("RESET WIFI DISCONNECTED");
    resetFunc();
  }

  if ( (millis() / 1000) % 2 ==  0)
  {
    ledValue = !ledValue;
  }

  digitalWrite(LED1pin, ledValue);

  if ( (millis() - last_read) > (1000) )    // 1 sec READ VALUES
  {
    Serial.println("ReadWriteValue..");

    if (Relays.size()>0)
    {
      static int ir = 0;
      ir = (++ir%Relays.size());
      Relays[ir].writevalues(); 
    }

    if (Probes.size()>0)
    {
      static int ip = 0;
      ip = (++ip%Probes.size());
      Probes[ip].readvalues(); 
    }

    last_read = millis();
    Serial.println("ReadWriteValue exit..");
  }
}

//***************************************************************************
void handleRoot()
{
  //Lista dei comandi accettati
  for (uint8_t i = 0; i < server.args(); i++)
  {
    String sname = server.argName(i);
    int value = server.arg(i).toInt();

    if ( sname == "L1" && Relays.size() > 0 ) Relays[0].set(value);
    if ( sname == "L2" && Relays.size() > 1 ) Relays[1].set(value);
    if ( sname == "L3" && Relays.size() > 2 ) Relays[2].set(value);
    if ( sname == "L4" && Relays.size() > 3 ) Relays[3].set(value);
    if ( sname == "L5" && Relays.size() > 4 ) Relays[4].set(value);
    if ( sname == "L6" && Relays.size() > 5 ) Relays[5].set(value);
    if ( sname == "L7" && Relays.size() > 6 ) Relays[6].set(value);
    if ( sname == "L8" && Relays.size() > 7 ) Relays[7].set(value);
  }

  String message;
  for (uint8_t i = 0; i < Relays.size(); i++)
  {
    message += "L" + String(i + 1) + ":" + Relays[i].GetOnOff() + "\n";
  }
  for (uint8_t i = 0; i < Probes.size(); i++)
  {
    message += "T" + String(i + 1) + ":" + Probes[i].GetTemperature() + "\n";
  }
  server.send(200, "text/plain", message);

  last_io = millis();

  Serial.println(message);
  digitalWrite(LED1pin, ledValue);
  ledValue = !ledValue;
}

//***************************************************************************
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);

  Serial.println(server.uri());
  digitalWrite(LED1pin, ledValue);
  ledValue = !ledValue;
}
