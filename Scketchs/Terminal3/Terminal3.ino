// MODULO 03
// elettrovalvole di gestione PDC e pompe
// scheda 4 x 2 rele  ( uscita 2-9)
// risposta: stato rele
// rev: 23 ago 2015

#include <dhprotocol.h>

#include <OneWire.h>
#include <SoftwareSerial.h>


DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  Slave.setup(3, 0, &mySerial);     // Terminal ID

  pinMode(2, OUTPUT);     // 2-10 relay.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );
}


void loop()
{
  /*******************************************************************************/
  if ( Slave.waitRequest(50) )
  {
    Slave.sendData();
    
    Serial.println( "");
    Serial.print( "Set Relay: " );
    
    for (int i = 0; i < 8; i++)
    {
	  Slave.sensor[i] = Slave.relay[i];
      digitalWrite(2 + i, !Slave.relay[i] );
	  if (i!=0)  Serial.print( "," );
      Serial.print( Slave.relay[i] );
    }
  }
  /*****************************************************************************/
  delay(10);
};

