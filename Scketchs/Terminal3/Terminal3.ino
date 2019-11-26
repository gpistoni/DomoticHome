// MODULO 03
// elettrovalvole di gestione PDC e pompe
// scheda 4 x 2 rele  ( uscita 2-9)
// risposta: stato rele
// rev: 23 ago 2015
// rev: 4 dic 2016
// rev: 23 mar 2018 
// rev: 20 ott 2019 

#include <cprobe.h>
#include <dhprotocol.h>
#include <OneWire.h>
#include <SoftwareSerial.h>


DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  Slave.setup(3, 0, &mySerial);     // Terminal ID

  for (int i = 0; i < 8; i++)       // 2-10 relay.
  {
    pinMode(2 + i, OUTPUT);
  }

  Serial.begin(57600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );
}


void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  /*******************************************************************************/
  if ( Slave.waitRequest(50) )
  {
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.print( "Current Relay PDC State: " );
    for (int i = 0; i < 8; i++)
    {
      Slave.sensor[i] = Slave.relay[i];
      digitalWrite(2 + i, !Slave.relay[i] );
      if (i != 0)  Serial.print( "," );
      Serial.print( Slave.relay[i] );
    }    
    Serial.println("");
    Slave.sendData();
  }
    delay(10);
};
