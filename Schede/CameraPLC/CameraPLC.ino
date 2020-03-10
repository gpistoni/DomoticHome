// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>

const char* ssid     = "ESP8266-AP";
const char* password = "123456789";

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
  //WiFi.softAP(ssid, password);

  //IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
//  Serial.println(IP);

  // Print ESP8266 Local IP Address
  //Serial.println(WiFi.localIP());


  pinMode(ENCODER1, OUTPUT);
  pinMode(ENCODER2, OUTPUT);
  
  pinMode(LIGHT, OUTPUT);

  pinMode(INPUT1, INPUT);
     
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Start server
  //server.begin();
  Serial.println("SETUP");
}

unsigned long  MasterClock =0;

void GenerateEncoder( int frequency)
{
  static int Encoder_State = 0;
  
  static const unsigned long interval = 1000 * 1000 / frequency / 2;
  static unsigned long previousMicro = 0;
  unsigned long currentMicro = micros();
  if (currentMicro - previousMicro >= interval)
  {
    // save the last time you updated the DHT values
    previousMicro = currentMicro;
    {
      digitalWrite(ENCODER1, Encoder_State);
      digitalWrite(ENCODER2, !Encoder_State);
     
      Encoder_State = !Encoder_State;
      if (Encoder_State) MasterClock++;
    }
  }
}

void CheckSendMessage()
{
  int val = digitalRead(INPUT1);
  if (val)
    Serial.println(MasterClock);
}

void loop()
{
  GenerateEncoder(2000); 
  
  int light = (MasterClock / 1000) % 2; 
  digitalWrite(LIGHT, light);

  CheckSendMessage();
   
}
