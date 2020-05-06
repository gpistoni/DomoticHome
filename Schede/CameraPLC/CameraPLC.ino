// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Hash.h>

const char* ssid     = "PistoniHome";
const char* password = "giaco1iren1dario";
WiFiUDP ClientUdp;
int localUdpPort = 1234;

unsigned long MASTER_FREQ = 3000;

int ENCODER1 = D0;
int ENCODER2 = D1;

int LIGHT = D2;
int INPUT1 = D7;

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  Serial.print("Setting AP (Access Point)…");

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.begin(ssid, password);


  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Udp
  ClientUdp.begin(localUdpPort);

  pinMode(ENCODER1, OUTPUT);
  pinMode(ENCODER2, OUTPUT);

  pinMode(LIGHT, OUTPUT);


  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(INPUT1, INPUT);
  attachInterrupt(INPUT1, interrupt_SendMessage, RISING);

  // Start server
  Serial.println("END SETUP");
}

unsigned long MasterClock = 0;

void GenerateMasterClock()
{
  static const unsigned long interval = 1000 * 1000 / MASTER_FREQ;
  MasterClock =  micros() / interval;
}

void SendEncoder()
{
  static int oldMasterClock = 0;
  if (MasterClock != oldMasterClock )
  {
    int value = MasterClock % 2;
    digitalWrite(ENCODER1, value);
    digitalWrite(ENCODER2, !value);
    oldMasterClock = MasterClock;

    digitalWrite(LED_BUILTIN, (MasterClock / 1000 % 2)); // 1Hz
  }
}

struct tPacket
{
  byte  revision; //0
  byte  plcRow;   //1
  int   tileID;   //2-5
  int   code;     //6-9
  byte  productiontest; //10
  float quota;    //11-14
  byte  terminator;   //15
} __attribute__ ((packed)) ;

void interrupt_SendMessage()
{
  const char ip[] = "192.168.1.113";
  ClientUdp.beginPacket(ip, 6365);
  tPacket pack;
  pack.revision = 11;
  pack.plcRow = 1;
  pack.tileID = 0;
  pack.code = 0;
  pack.productiontest = 1;
  pack.quota = MasterClock;
  pack.terminator = 0;

  ClientUdp.write((uint8_t *)&pack, sizeof(pack) );
  ClientUdp.endPacket();
  //LOG
  Serial.print("Send Packet:");
  Serial.println(MasterClock);
}

void Light()
{
  int light = (MasterClock / 3000) % 2;
  digitalWrite(LIGHT, light);
  //Serial.println("Set Light:");
}

void loop()
{
  GenerateMasterClock();
  SendEncoder();
  Light();
}
