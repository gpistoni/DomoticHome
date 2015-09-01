//#define DISABLE_TRACE
#define DISABLE_SD

#include <dhprotocol.h>
#include <DHSdDb.h>

#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

#include "webserver.h"

// terminali
DHProtocol T[8];

SoftwareSerial mySerial(8, 9, 1);  //RX, TX, inverse logic (signal=5v)

// MAC address for the ethernet controller.  -----------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

// IP address for the controller:  -----------------------------
IPAddress ip(192, 168, 1, 175);                         //<<-- IP
//IPAddress gateway(172, 31, 8, 1);                     //<<-- GATEWAY
//IPAddress subnet(255, 255, 255, 0);                   //<<-- SUBNET

// Pins 10, 11, 12 and 13 are reserved for interfacing with the Ethernet module and should not be used otherwise
// Pin 10 is reserved for the Wiznet interface, SS for the SD card is on Pin 4.
// There is a built-in LED connected to digital pin 9.
EthernetServer server(80);

//SELECT (ON OFF) pins
#define SD_SELECT 4
#define ETHERNET_SELECT 10

DHSdDb db;

void setup()
{
  T[1].setup(0, 1, &mySerial );  // -
  T[2].setup(0, 2, &mySerial );  // --
  T[3].setup(0, 3, &mySerial );   // rele' pdc
  T[4].setup(0, 4, &mySerial );  // temp caldaie
  T[5].setup(0, 5, &mySerial );   // rele pavimento
  T[6].setup(0, 6, &mySerial );  // --
  T[7].setup(0, 7, &mySerial );  // --

  Serial.begin(9600);
  OUTLN("System Start");

  //inifile ************************************************************
  pinMode(SD_SELECT, OUTPUT);
  digitalWrite(SD_SELECT, HIGH); // disable SD card

  pinMode(ETHERNET_SELECT, OUTPUT);
  digitalWrite(ETHERNET_SELECT, HIGH); // disable Ethernet

#ifndef DISABLE_SD
  OUTLN("Initializing SD card...");
  if (!SD.begin(4))
  {
    OUTLN("initialization failed!");
    return;
  }
  OUTLN("initialization done.");

  //sample
  db.WriteValue("pinco", "pallino", "100");
  //Serial.print( db.ReadValue("pinco", "pallino") );
#endif

  //ethernet ************************************************************
  Ethernet.begin(mac, ip);
  server.begin();

  // give the sensor and Ethernet shield time to set up:
  delay(1000);

  OUTLN("server is at ");
  OUTLN(Ethernet.localIP());
}

int count = 0;

void loop()
{
   listenForEthernetClients();

  count++;
  if ( T[2].checkTiming(2000) )
  {
//    T[2].relay[0] = 0;
    T[2].sendRequest();
    T[2].waitData( 100 );
    return;
  };
  if ( T[3].checkTiming(3000) )
  {
    //estate  full
    //T[3].relay[0] = 1;
    //T[3].relay[1] = 0;
    //T[3].relay[2] = 1;
    //T[3].relay[3] = 0;
    //estate  night
    //T[3].relay[0] = 1;
    //T[3].relay[1] = 0;
    //T[3].relay[2] = 1;
    //T[3].relay[3] = 1;
    //off
    //T[3].relay[0] = 0;
    //T[3].relay[1] = 0;
    //T[3].relay[2] = 0;
    //T[3].relay[3] = 0;
    
//    T[3].relay[4] = 0;
//    T[3].relay[5] = 0;
//    T[3].relay[6] = 0;
//    T[3].relay[7] = 0;

    T[3].sendRequest();
    T[3].waitData( 100 );
    return;
  };
  if ( T[4].checkTiming(4000) )
  {
 //   T[4].relay[0] = 1;

    T[4].sendRequest();
    T[4].waitData( 100 );
    return;
  };
  if ( T[5].checkTiming(10000) )
  {
    T[5].relay[0] = 0;
    T[5].relay[1] = 1;
    T[5].relay[2] = 1;
    T[5].relay[3] = 1;
    T[5].relay[4] = 1;
    T[5].relay[5] = 1;
    T[5].relay[6] = 1;
    T[5].relay[7] = 1;

    T[5].sendRequest();
    T[5].waitData( 100 );
    return;
  };

  Serial.print(".");
  //OUT( millis() );
  //OUT( " freeMemory()=" );
  //OUTLN( freeMemory() );
  delay(100);
}



