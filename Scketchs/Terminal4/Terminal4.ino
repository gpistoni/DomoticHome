// MODULO 04
// sonde temperatura locale caldaia
// ingressi sonde 2-9 onewire con resisteza pullup
// send: tempertaura in sensor [0..8] 
// rev: 16 ago 2015

#include <cdht.h>
#include <dhprotocol.h>
#include <cprobe.h>

#include <DHT.h>
#include <OneWire.h>
#include <SoftwareSerial.h>


CProbe  Probes;

DHProtocol Slave;
SoftwareSerial mySerial(10, 12, TRUE);          // RX 10, TX 12 Serial, inverse logic


void setup()
{
  Slave.setup(4, 0, &mySerial);     		// Terminal ID
  Probes.setup(2,3,4,5,6,7,8,9);        	// 4 temp
 
  Serial.begin(9600);                     	// disabilito le seriali 
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );

}

unsigned long old_Read = 0;

void loop()
{
   
  if ( Slave.waitRequest( 50 ) )
  {
     Slave.sendData();
     return;
  }
  
/*******************************************************************************/
  unsigned long now = millis();               // Terminal ID
  if ( now - old_Read >= 10000)  //leggo probe ogni 2 secondi
  {
    old_Read = now;

    Probes.readvalues();

    for ( int i = 0; i < Probes.nums; i++)
    {
      Slave.sensor[i] = Probes.t[i] * 10;
    
      Serial.println( "");
      Serial.print( "Probe:" );
      Serial.print( Slave.sensor[i] );
     }
  }
  /*****************************************************************************/
};

