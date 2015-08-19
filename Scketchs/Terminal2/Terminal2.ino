#include <DHT.h>
#include <OneWire.h>
#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

#include "chdt.cpp"
#include "protocol.cpp"
#include "probe.cpp"

CDht    SensorsHDT;
CProbe  Probes;

CCom Slave;
SoftwareSerial mySerial(10, 11);     // 10,11 Serial


void setup()
{
  SensorsHDT.setup(4);          // 4,5,6 DHT
  Probes.setup(7);                   // 7 temp

  Slave.setup(2, 0, &mySerial, 9600);     // Terminal ID

  Serial.begin(9600);
  while (!Serial); //wait

  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.id );
    
  pinMode(14, OUTPUT);                // 14(A0),15(A1) Relay
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);                
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);                
  pinMode(19, OUTPUT);
  
}

unsigned long old_ReadHDT = 0;
unsigned long old_ReadProbe = 0;
unsigned long old_RelayUpdate = 0;

void loop()
{
  unsigned long now = millis();               // Terminal ID
  bool HaveTosend = false;

  int id = Slave.id;

  //*****************************************************************************
  if ( now - old_ReadHDT >= 10000)  //leggo dht ogni 10 secondi
  {
    old_ReadHDT = now;

    SensorsHDT.readvalues();

    for ( int i = 0; i < SensorsHDT.nums; i++)
    {
      Slave.sensor[i] = SensorsHDT.h[i] * 10;
      Slave.sensor[8+i] = SensorsHDT.t[i] * 10;

      Serial.println( "");
      Serial.print( Slave.id );
      Serial.print( " - H:" );
      Serial.print( Slave.sensor[i] );
      Serial.print( " \tT:" );
      Serial.print( Slave.sensor[8+i] );
    }
    HaveTosend = true;
  }
  //*****************************************************************************
  else if ( now - old_ReadProbe >= 2000)  //leggo probe ogni 1 secondi
  {
    old_ReadProbe = now;

    Probes.readvalues();

    for ( int i = 0; i < Probes.nums; i++)
    {
      Slave.sensor[16+i] = Probes.t[i] * 10;
      Serial.println( "");
      Serial.print( "Probe:" );
      Serial.print( Slave.sensor[16+i] );
    }
    HaveTosend = true;
  }
  /*******************************************************************************/
  if ( Slave.waitRequest() )
  {
    for ( int i = 0; i < 6; i++)
    {
      digitalWrite(14 + i, Slave.relay[i] );
      Serial.println( "");
      Serial.print( "Relay" );
      Serial.print( i );
      Serial.print( ":" );
      Serial.print( Slave.relay[i] );
    }

    Slave.sendData();
    
  }
  /*****************************************************************************/

  if (HaveTosend)
  {
 //   Slave.sendData();
  }
  delay(5);
};

