// MODULO 01
// Temperature stanze
// scheda 8 DHT
// rev: 23 ago 2015

#include <cdht.h>
#include <dhprotocol.h>
#include <cprobe.h>

#include <DHT.h>
#include <OneWire.h>
#include <SoftwareSerial.h>

CDht    SensorsHDT;

DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  SensorsHDT.setup(2,3,4,5,6,7,8,9,10);          // 4,5,6... DHT

  Slave.setup(1, 0, &mySerial);     // Terminal ID
  
  Serial.begin(9600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );
  
}

unsigned long old_ReadHDT = 0;

void loop()
{
  if ( Slave.waitRequest( 50 ) )
  {
     Slave.sendData();
   }
  
/*******************************************************************************/
  unsigned long now = millis();               // Terminal ID
  if ( now - old_ReadHDT >= 5000)  //leggo probe ogni 2 secondi
  {
    old_ReadHDT = now;

    SensorsHDT.readvalues();
    Serial.println( "readvalues" );
 
    for ( int i = 0; i < SensorsHDT.nums; i++)
    {
      if (SensorsHDT.h[i]>0)
        Slave.sensor[i] = SensorsHDT.h[i] * 10;
      if (SensorsHDT.t[i]>0)
        Slave.sensor[10+i] = SensorsHDT.t[i] * 10;

      Serial.println("");
      Serial.print( i );
      Serial.print( " - H:" );
      Serial.print( SensorsHDT.h[i] );
      Serial.print( " \tT:" );
      Serial.print( SensorsHDT.t[i] );
      Serial.print( " \tTp:" );
      Serial.print( SensorsHDT.hic[i] );
    }
  }
  
  /*****************************************************************************/
};


