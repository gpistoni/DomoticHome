#include <ESP8266WiFi.h>

WiFiServer server(80);

// To flash the new software to our SONOFF, we have to start Sonoff in flash mode. 
// Follow this steps process:Connection of USB converter to SONOFFHold down the SONOFF buttonToggle 
// the switch to apply power to the Sonoff circuitThen, we can release the SONOFF buttonAfter SONOFF
// is in flash mode, we can upload new software.This program is very simple, so it is great for first flashing.

// Ip utilizzati  210, 212, 214, 216, 218

// Setup IP
IPAddress local_IP(192, 168, 1, 214);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Replace with your network credentials
const char* ssid = "PistoniHome";
const char* password = "giaco1iren1dario";

String web_on_html = "1 <p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
String web_off_html = "0 <p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";

int gpio_13_led = 13;
int gpio_12_relay = 12;

// NORMALY ON
int stato = 1;

//declare reset function @ address 0
void(*resetFunc) (void) = 0;

void setup(void)
{
  //  Init
  pinMode(gpio_13_led, OUTPUT);
  pinMode(gpio_12_relay, OUTPUT);

  // Stato di default
  digitalWrite(gpio_13_led, !stato);
  digitalWrite(gpio_12_relay, stato);

  Serial.begin(115200);
  delay(10000);

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
    digitalWrite(gpio_13_led, LOW);
    delay(200);
    digitalWrite(gpio_13_led, HIGH);
    delay(100);
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

  server.begin();
  Serial.println("Server ready..");
}



unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
unsigned long last_io = millis();
static unsigned long last_act = 0;


void loop(void)
{
  WiFiClient client = server.available();

  if (client)
  { 
    // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    String header;

    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { 
      // loop while the client's connected
      currentTime = millis();
      if (client.available())
      { 
        // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n')                      // if the byte is a newline character
        {
          Serial.print(millis()/1000.0);
          Serial.print(" ");
          Serial.print(header);

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          // turns the GPIOs on and off
          if (header.indexOf("GET /on") >= 0)
          {
            stato = HIGH;
            digitalWrite(gpio_13_led, stato);
            delay(100);
            digitalWrite(gpio_13_led, !stato);
            delay(100);
            Serial.print(millis()/1000.0);
            Serial.println(" State ON");
            last_io = millis();
          }
          else if (header.indexOf("GET /off") >= 0)
          {
            stato = LOW;
            digitalWrite(gpio_13_led, stato);
            delay(100);
            digitalWrite(gpio_13_led, !stato);
            delay(100);
            Serial.print(millis()/1000.0);
            Serial.println(" State OFF");
            last_io = millis();
          }

          // Response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          if (stato)
            client.println(web_on_html);
          else
            client.println(web_off_html);
          break;
        }
      }
    }
  }

  //activity
  if ( millis() - last_act > 1000 )  // 30 sec
  {
    digitalWrite(gpio_13_led, stato);
    delay(5);
    last_act = millis();
  }


  //Force set on
  if ( millis() - last_io > 1000 * 60 * 10 ||  WiFi.status() != WL_CONNECTED ) // 10 minutes
  {
    Serial.print(millis()/1000.0);
    Serial.println(" FORCE SET ON");
    stato = true;
  }

  //restart
  if ( millis() - last_io > 1000 * 60 * 60 ||  WiFi.status() != WL_CONNECTED ) // 60 minutes
  {
    Serial.print(millis()/1000.0);
    Serial.println(" RESET");
    resetFunc();
  }

  digitalWrite(gpio_13_led, !stato);
  digitalWrite(gpio_12_relay, stato);
}
