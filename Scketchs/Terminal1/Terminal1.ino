// MODULO 01
// Temperature stanze
// scheda 8 DHT
// rev: 23 ago 2015

#include <cdht.h>
#include <dhprotocol.h>
#include <cprobe.h>

#include <DHT.h>
#include <DHOneWire.h>
#include <SoftwareSerial.h>

CDht    SensorsHDT;

DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  SensorsHDT.setup(2,3,4,5,6,7,8,9);          // 4,5,6... DHT

  Slave.setup(1, 0, &mySerial);     // Terminal ID
  
  Serial.begin(9600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );
}

unsigned long old_ReadHDT = 0;

void loop()
{
  if ( Slave.waitRequest( 100 ) )
  {
     Slave.sendData();
   }
  
/*******************************************************************************/
  unsigned long now = millis();               // Terminal ID
  if ( now - old_ReadHDT >= 6000)             // leggo probe ogni 2 secondi
  {
    old_ReadHDT = now;

    SensorsHDT.readvalues();
    Serial.println( "readvalues" );
 
    for ( int i = 0; i < SensorsHDT.nums; i++)
    {
      if (SensorsHDT.t[i]>0)
        Slave.sensor[i] = Slave.sensor[i] * 0.9 + SensorsHDT.t[i];
      if (SensorsHDT.h[i]>0)
        Slave.sensor[8+i] = Slave.sensor[8+i]* 0.9 + SensorsHDT.h[i];
      if (SensorsHDT.hic[i]>0)
        Slave.sensor[16+i] = Slave.sensor[16+i] * 0.9 + SensorsHDT.hic[i];

      Serial.println("");
      Serial.print( i );
      Serial.print( " - T:" );
      Serial.print( SensorsHDT.t[i] );
      Serial.print( " H:" );
      Serial.print( SensorsHDT.h[i] );
      Serial.print( " Tp:" );
      Serial.print( SensorsHDT.hic[i] );

      Serial.print( " \t- T:" );
      Serial.print( Slave.sensor[i] );
      Serial.print( " H:" );
      Serial.print( Slave.sensor[8+i] );
      Serial.print( " Tp:" );
      Serial.print( Slave.sensor[16+i] );
    }
  }
  
  /*****************************************************************************/
};


