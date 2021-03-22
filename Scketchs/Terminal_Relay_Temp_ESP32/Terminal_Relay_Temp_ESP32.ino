#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include <cprobe.h>
#include <crelay.h>


//**************************************************
// Nodi utilizzati:
//**************************************************
// 21   ESP32   Relay                   Luci esterne
// 22   ESP32   Relay + Imput Temps     Gestione Caldaie
//**************************************************

WebServer server(80);

// Setup IP
IPAddress local_IP(192, 168, 1, 22);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

#include <dhlibrary.h>

CRelay  Relays;
CProbe  Probes;

// TIMING
void handleRoot();
void handleNotFound();

void setup(void)
{
  setupWIFI();

  // Init Relay
  Relays.setup( 18, 17, 16, 4, 19, 21, 22, 23 );  // 8 rele'

  // Init Probes
  Probes.setup(14, 27, 26, 25, 35, 34, 39, 36);   // 8 temperature input

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

  if ( millis() % 10000 == 0)
  {
    digitalWrite(LED1pin, ledValue);
    ledValue = !ledValue;
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

    if ( sname == "L1" ) Relays.set(0,  value);
    if ( sname == "L2" ) Relays.set(1,  value);
    if ( sname == "L3" ) Relays.set(2,  value);
    if ( sname == "L4" ) Relays.set(3,  value);
    if ( sname == "L5" ) Relays.set(4,  value);
    if ( sname == "L6" ) Relays.set(5,  value);
    if ( sname == "L7" ) Relays.set(6,  value);
    if ( sname == "L8" ) Relays.set(7,  value);
  }

  // Update Relay
  Relays.writeOutput();

  String message = "Done\n\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  for (uint8_t i = 0; i < 8; i++)
  {
    message += " T" + String(i) + ": " + Probes.Temperature(i) + "\n";
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
