// MODULO 02
// luci esterne
// rev 22 mar 2018

#include <dhprotocol.h>
#include <OneWire.h>
#include <SoftwareSerial.h>


DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  Slave.setup(2, 0, &mySerial);     // Terminal ID

  for (int i = 0; i < 8; i++)   // 2-10 relay.
  {
    pinMode(2 + i, OUTPUT);
  }

  Serial.begin(57600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );
}

bool b;

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  /*******************************************************************************/
  if ( Slave.waitRequest(50) )
  {
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.print( "Current Relay State: " );
    for (int i = 0; i < 8; i++)
    {
      Slave.sensor[i] = Slave.relay[i];
      digitalWrite(2 + i, !Slave.relay[i] );
      if (i != 0)  Serial.print( "," );
      Serial.print( Slave.relay[i] );
    }
    
    Slave.sendData();
  }
};

