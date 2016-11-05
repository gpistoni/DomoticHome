// MODULO 02
// luci esterne
// rev: 10 nov 2016

#include <dhprotocol.h>

#include <OneWire.h>
#include <SoftwareSerial.h>


DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  Slave.setup(2, 0, &mySerial);     // Terminal ID

  pinMode(2, OUTPUT);     // 2-5 relay.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );
}

bool b;

void loop()
{  
  /*******************************************************************************/
  if ( Slave.waitRequest(50) )
  {
    Slave.relay[0] = !Slave.relay[0];
     
    Serial.print( "\nSet Relay: " );

    for (int i = 0; i < 4; i++)
    {
      Slave.sensor[i] = Slave.relay[i];
      digitalWrite(2 + i, !Slave.relay[i] );
      if (i != 0)  Serial.print( "," );
      Serial.print( Slave.relay[i] );
    }
    Slave.sendData();
  } 
};

