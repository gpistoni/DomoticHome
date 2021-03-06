#include <WiFi.h>
#include <WebServer.h>

//**************************************************
// Nodi utilizzati:
//**************************************************
// 21   ESP8266   Relay    Luci esterne
//**************************************************

WebServer server(80);

// Setup IP
IPAddress local_IP(192, 168, 1, 21);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Replace with your network credentials
const char* ssid = "PistoniHome";
const char* password = "giaco1iren1dario";

uint8_t LED1pin = 2;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

// RELAY ("L1".."L8") su ESP32 come da schema [IO-ESP32-30-Relay]
const int gpio_relay[8] = { 18, 17, 16, 4, 19, 21, 22, 23  };
int relay[8];


// TIMING
unsigned long last_io = millis();
unsigned long ledValue = 0;

//declare reset function @ address 0
void(*resetFunc) (void) = 0;

void handleRoot();
void handleNotFound();

void setup(void)
{
  Serial.begin(115200);
  delay(1000);

  // Init
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);

  // Init Relay
  for (int i = 0; i < 8; i++)
  {
    relay[i] = 0;
    pinMode(gpio_relay[i], OUTPUT);
    digitalWrite(gpio_relay[i], !relay[i]);
  };

  // Setup Connessione
  if (!WiFi.config(local_IP, gateway, subnet))
  {
    Serial.println("STA Failed to configure");
  }
  Serial.println("Connecting to single wifi..");

  // Wait for multiple connection
  Serial.print("Try to Connect to WIFI");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  unsigned long tout = millis() + 10000;
  while (WiFi.status() != WL_CONNECTED && millis() < tout)
  {
    Serial.print(".");
    digitalWrite(LED1pin, LOW);
    delay(200);
    digitalWrite(LED1pin, HIGH);
    delay(200);
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());

  //risponditore
  server.on("/", HTTP_GET, handleRoot);

  //risponditore
  server.on("/inline", HTTP_GET, []() {
    server.send(200, "text/plain", "this works as well");
  });

  //risponditore not found
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Server ready..");
}


unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
static unsigned long last_act = 0;


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

    if ( sname == "L1" ) relay[0] = value;
    if ( sname == "L2" ) relay[1] = value;
    if ( sname == "L3" ) relay[2] = value;
    if ( sname == "L4" ) relay[3] = value;
    if ( sname == "L5" ) relay[4] = value;
    if ( sname == "L6" ) relay[5] = value;
    if ( sname == "L7" ) relay[6] = value;
    if ( sname == "L8" ) relay[7] = value;
  }

  // Update Relay
  for (int i = 0; i < 8; i++)
  {
    if (gpio_relay[i] > 0)  digitalWrite(gpio_relay[i], !relay[i]);
  };

  String message = "Done\n\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(200, "text/plain", message);

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
