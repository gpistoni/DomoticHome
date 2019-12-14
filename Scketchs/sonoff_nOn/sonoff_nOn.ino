#include <ESP8266WiFi.h>

WiFiServer server(80);

// Ip utilizzati  210, 212, 218

// Setup IP
IPAddress local_IP(192, 168, 1, 218);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Replace with your network credentials
const char* ssid[3]     = { "PistoniHome", "PistoniHome1", "PistoniHome2" };
const char* password = "giaco1iren1dario";

String web_on_html = "1 <p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
String web_off_html = "0 <p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";

int gpio_13_led = 13;
int gpio_12_relay = 12;

int stato = 1;
static unsigned long last_io = millis();

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
  Serial.println("Connecting to multiple wifi..");

  // Wait for multiple connection
  int i = 0;
  WiFi.begin(ssid[i], password);
  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid[i], password);
    Serial.println("");
    Serial.print("Try to Connect to WIFI");
    Serial.print(ssid[i]);

    unsigned long tout = millis() + 10000;
    while (WiFi.status() != WL_CONNECTED && millis() < tout)
    {
      Serial.print(".");
      digitalWrite(gpio_13_led, LOW);
      delay(1000);
      digitalWrite(gpio_13_led, HIGH);
      delay(1000);
    }
    if (WiFi.status() != WL_CONNECTED)
    {
      i = ++i % 3;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print(ssid[i]);
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

  //  server.on("/", []()
  //  {
  //    if (digitalRead(gpio_12_relay) == HIGH)  {
  //      server.send(200, "text/html", web_on_html);
  //    } else {
  //      server.send(200, "text/html", web_off_html);
  //    }
  //    last_io = millis();
  //  });
  //
  //  server.on("/on", []()
  //  {
  //    server.send(200, "text/html", web_on_html);
  //    stato = HIGH;
  //    digitalWrite(gpio_13_led, stato);
  //    delay(100);
  //    digitalWrite(gpio_13_led, !stato);
  //    delay(100);
  //    Serial.print(millis());
  //    Serial.println(" State ON");
  //    last_io = millis();
  //  });
  //
  //  server.on("/off", []() {
  //    server.send(200, "text/html", web_off_html);
  //    stato = LOW;
  //    digitalWrite(gpio_13_led, stato);
  //    delay(100);
  //    digitalWrite(gpio_13_led, !stato);
  //    delay(100);
  //    Serial.print(millis());
  //    Serial.println(" State OFF");
  //    last_io = millis();
  //  });

  last_io = millis();
  server.begin();
  Serial.println("Server ready..");
}

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void loop(void)
{
  static unsigned long last = 0;

  WiFiClient client = server.available();

  if (client)
  { // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    currentTime = millis();
    previousTime = currentTime;
    String header;

    while (client.connected() && currentTime - previousTime <= timeoutTime)
    {                                       // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                                     // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n')                      // if the byte is a newline character
        {
          Serial.println(header);
          
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
            Serial.print(millis());
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
            Serial.print(millis());
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
  if ( millis() - last > 30000 )  // 30 sec
  {
    digitalWrite(gpio_13_led, stato);
    delay(5);
    digitalWrite(gpio_13_led, !stato);
    delay(5);
    last = millis();
    Serial.println(millis());
  }

  //restart
  if ( millis() - last_io > 360000 ||  WiFi.status() != WL_CONNECTED ) // 60 minutes
  {
    Serial.println(millis());
    Serial.println("RESET");
    resetFunc();
  }

  digitalWrite(gpio_13_led, !stato);
  digitalWrite(gpio_12_relay, stato);
}
