/*
  Simple Wifi Switch
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>

MDNSResponder mdns;
ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);


// Replace with your network credentials
const char* ssid_1 = "PistoniHome";
const char* ssid_2 = "PistoniHome";
const char* password_1 = "giaco1iren1dario";
const char* password_2 = "giaco1iren1dario";

String web_on_html = "1 <p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
String web_off_html = "0 <p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";

int gpio_13_led = 13;
int gpio_12_relay = 12;

int stato = 0;
static unsigned long last_io = 0;

//declare reset function @ address 0
void(*resetFunc) (void) = 0; 

void setup(void) 
{
  //  Init
  pinMode(gpio_13_led, OUTPUT);
  pinMode(gpio_12_relay, OUTPUT);

  Serial.begin(115200);
  delay(5000);

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);
    
  Serial.println("Connecting to multiple wifi..");

  // Wait for connection
  while (wifiMulti.run() != WL_CONNECTED)
  {
    digitalWrite(gpio_13_led, LOW);
    delay(500);
    Serial.print(".");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.status());
    digitalWrite(gpio_13_led, HIGH);
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) 
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() 
  {
    if (digitalRead(gpio_12_relay) == HIGH)  {
      server.send(200, "text/html", web_on_html);
    } else {
      server.send(200, "text/html", web_off_html);
    }
        last_io = millis();
  });

  server.on("/on", []() 
  {
    server.send(200, "text/html", web_on_html);
    stato = HIGH;
    digitalWrite(gpio_13_led, stato);
    delay(200);
    digitalWrite(gpio_13_led, !stato);
    delay(200);
        last_io = millis();
  });

  server.on("/off", []() {
    server.send(200, "text/html", web_off_html);
    stato = LOW;
    digitalWrite(gpio_13_led, stato);
    delay(200);
    digitalWrite(gpio_13_led, !stato);
    delay(200);
    last_io = millis();
  });

  server.begin();
  Serial.println("Server ready..");
}

void loop(void)
{
  
  static unsigned long last = 0;
  if ( millis() - last > 30 /*sec*/ * 1000 )  //30 sec
  {
    digitalWrite(gpio_13_led, stato);
    delay(5);
    digitalWrite(gpio_13_led, !stato);
    delay(5);
    last = millis();
    Serial.println(".");
  }

  if ( millis() - last_io > 30 * 60 * 1000 ) // 30 minutes
  {
    resetFunc();
  }

  //client
  server.handleClient();

  digitalWrite(gpio_13_led, !stato);
  digitalWrite(gpio_12_relay, stato);
}
