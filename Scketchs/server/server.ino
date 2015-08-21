#include <DHT.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

#include <dhprotocol.h>
#include "webserver.h"
#include "sddb.h"

// terminali
DHProtocol T[8];

SoftwareSerial mySerial(8, 9, TRUE);  //RX, TX, inverse logic (signal=5v)

// MAC address for the ethernet controller.  -----------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

// IP address for the controller:  -----------------------------
IPAddress ip(172, 31, 11, 175);                         //<<-- IP
//IPAddress gateway(172, 31, 8, 1);                     //<<-- GATEWAY
//IPAddress subnet(255, 255, 255, 0);                   //<<-- SUBNET

 // Pins 10, 11, 12 and 13 are reserved for interfacing with the Ethernet module and should not be used otherwise
 // Pin 10 is reserved for the Wiznet interface, SS for the SD card is on Pin 4. 
 // There is a built-in LED connected to digital pin 9.
 EthernetServer server(80);

//SELECT (ON OFF) pins
#define SD_SELECT 4
#define ETHERNET_SELECT 10

void setup()
{ 
  T[1].setup(0, 1, 16, &mySerial );  // -
  T[2].setup(0, 2, 16, &mySerial );  // --
  T[3].setup(0, 3, 0, &mySerial );   // rele' pdc
  T[4].setup(0, 4, 16, &mySerial );  // temp caldaie
  T[5].setup(0, 5, 0, &mySerial );   // rele pavimento
  T[6].setup(0, 6, 16, &mySerial );  // --
  T[7].setup(0, 7, 16, &mySerial );  // --

  Serial.begin(9600);
  Serial.println("System Start");

 //inifile ************************************************************
  pinMode(SD_SELECT, OUTPUT);
  digitalWrite(SD_SELECT, HIGH); // disable SD card
  
  pinMode(ETHERNET_SELECT, OUTPUT);
  digitalWrite(ETHERNET_SELECT, HIGH); // disable Ethernet
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.print("initialization done.");

//sample
  SDDB::WriteValue("pinco", "pallino", "100");

  Serial.print( SDDB::ReadValue("pinco", "pallino") );
 
//ethernet ************************************************************
  Ethernet.begin(mac, ip);
  server.begin();

  // give the sensor and Ethernet shield time to set up:
  delay(1000);
 
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  digitalWrite(10,HIGH);
}

int count = 0;

void loop()
{
  listenForEthernetClients();
    
  count++;
  if ( T[3].checkTiming(5000) )
  {
    T[3].relay.bits.b1 = 0;
    T[3].relay.bits.b2 = 0;
    T[3].relay.bits.b3 = 1;
    T[3].relay.bits.b4 = 0;
    T[3].relay.bits.b5 = 0;
    T[3].relay.bits.b6 = 0;
    T[3].relay.bits.b7 = 0;
    T[3].relay.bits.b8 = 0;
    
    T[3].sendRequest();
    T[3].waitData( 100 );
    return;
  };
  if ( T[4].checkTiming(5000) )
  {
    T[4].relay.bits.b1 = 0;
    T[4].relay.bits.b2 = 1;
    T[4].relay.bits.b3 = 0;
    T[4].relay.bits.b4 = 0;
    T[4].relay.bits.b5 = 0;
    T[4].relay.bits.b6 = 1;
    T[4].relay.bits.b7 = 0;
    T[4].relay.bits.b8 = 0;
    
    T[4].sendRequest();
    T[4].waitData( 100 );
    return;
  };
  if ( T[5].checkTiming(15000) )
  {
    T[5].relay.bits.b1 = 0;
    T[5].relay.bits.b2 = 0;
    T[5].relay.bits.b3 = 0;
    T[5].relay.bits.b4 = 0;
    T[5].relay.bits.b5 = 0;
    T[5].relay.bits.b6 = 0;
    T[5].relay.bits.b7 = 0;
    T[5].relay.bits.b8 = 0;
    
    T[5].sendRequest();
    T[5].waitData( 100 );
    return;
  };

  Serial.println("");
  Serial.print( millis());
  Serial.print(" freeMemory()=");
  Serial.print(freeMemory());
  delay(1000);
}


