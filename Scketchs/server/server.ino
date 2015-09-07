#include <dhprotocol.h>

#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>

#include "webserver.h"

// terminali
DHProtocol T[8];

SoftwareSerial mySerial(8, 9, 1);  //RX, TX, inverse logic (signal=5v)

// MAC address for the ethernet controller.  -----------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

// IP address for the controller:  -----------------------------
IPAddress ip(192, 168, 1, 200);                         //<<-- IP
//IPAddress gateway(172, 31, 8, 1);                     //<<-- GATEWAY
//IPAddress subnet(255, 255, 255, 0);                   //<<-- SUBNET

// Pins 10, 11, 12 and 13 are reserved for interfacing with the Ethernet module and should not be used otherwise
// Pin 10 is reserved for the Wiznet interface, SS for the SD card is on Pin 4.
// There is a built-in LED connected to digital pin 9.
EthernetServer server(80);

#define ETHERNET_SELECT 10

void setup()
{ 
  Serial.begin(9600);
  while(!Serial);
  
  OUTLN("System Start");
  
  T[1].setup(0, 1, &mySerial );  // -
  T[2].setup(0, 2, &mySerial );  // --
  T[3].setup(0, 3, &mySerial );  // rele' pdc
  T[4].setup(0, 4, &mySerial );  // temp caldaie
  T[5].setup(0, 5, &mySerial );  // rele pavimento
  T[6].setup(0, 6, &mySerial );  // --
  T[7].setup(0, 7, &mySerial );  // --

  //inifile ************************************************************
  pinMode(ETHERNET_SELECT, OUTPUT);
  digitalWrite(ETHERNET_SELECT, HIGH); // disable Ethernet

  //ethernet ************************************************************
  Ethernet.begin(mac, ip);
  server.begin();

  // give the sensor and Ethernet shield time to set up:
  delay(2000);

  OUT("server is at ");
  OUTLN(Ethernet.localIP());
}

void loop()
{
  for (int t = 1; t < 8; t++)
  {
    if ( T[t].checkTiming(2000) )
    {
      T[t].sendRequest();
      T[t].waitData( 100 );
    };
    
    listenForEthernetClients();
  };
  
  delay(10);
}



