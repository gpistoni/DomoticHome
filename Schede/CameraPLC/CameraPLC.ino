// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Hash.h>

#define _PACKET 0

const char* ssid     = "PistoniHome";
const char* password = "giaco1iren1dario";

#if _PACKET
WiFiUDP ClientUdp;
int localUdpPort = 1234;
#endif

unsigned long MASTER_FREQ = 4000;

int ENCODER1 = D0;
int ENCODER2 = D1;

int LIGHT = D2;
int INPUT1 = D7;

void setup()
{
  pinMode(ENCODER1, OUTPUT);
  pinMode(ENCODER2, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(INPUT1, INPUT);

  attachInterrupt(INPUT1, interrupt_SendMessage, RISING);

  // Serial port for debugging purposes
  Serial.begin(115200);

#if _PACKET
  Serial.print("Setting AP (Access Point)…");

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.begin(ssid, password);

  // Wait for connection------------------------------------------------------------
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, 1);
    delay(100);
    digitalWrite(LED_BUILTIN, 0);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Udp
  ClientUdp.begin(localUdpPort);
#endif

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
  int   index;     //6-9
  byte  productiontest; //10
  float quota;    //11-14
  byte  terminator;   //15
} __attribute__ ((packed)) ;

int tileID = 1;
int LightCounter = 0;
int LightStatus = 0;

void interrupt_SendMessage()
{
#if _PACKET
  const char ip[] = "192.168.1.113";
  ClientUdp.beginPacket(ip, 6365);
  tPacket pack;
  pack.revision = 11;
  pack.plcRow = 1;
  pack.tileID = tileID++;
  pack.index = 1;
  pack.productiontest = 1;
  pack.quota = MasterClock;
  pack.terminator = 0;

  ClientUdp.write((uint8_t *)&pack, sizeof(pack) );
  ClientUdp.endPacket();
#endif

  if ( !LightStatus ) LightCounter++;
  if ( LightStatus ) LightCounter--;

  //LOG
  Serial.print("Send Packet at quota:");
  Serial.println(MasterClock);
  Serial.print(" Light counter:");
  Serial.println(LightCounter);
}

void Light()
{
  if (LightCounter < 0 ) LightStatus = 0;
  if (LightCounter > 5 ) LightStatus = 1;

  digitalWrite(LIGHT, LightStatus);
  //Serial.println("Set Light:");
}

void loop()
{
  GenerateMasterClock();
  SendEncoder();
  Light();
}
