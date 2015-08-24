// MODULO 03
// elettrovalvole di gestione PDC e pompe
// scheda 4 x 2 rele  ( uscita 2-9)
// nessun dato di risposta
// rev: 13 ago 2015

#include <dhprotocol.h>

#include <OneWire.h>
#include <SoftwareSerial.h>


DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial


void setup()
{
  Slave.setup(3, 0, &mySerial);     // Terminal ID
  
/*
  Serial.begin(9600);
  while (!Serial); //wait
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.id );
*/

  pinMode(2, OUTPUT);     // 2-10 relay.
  pinMode(3, OUTPUT);       
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

}

unsigned long old_ReadHDT = 0;


void loop()
{
  unsigned long now = millis();               // Terminal ID
  bool HaveTosend = false;

  //int id = Slave.m_id;

  /*******************************************************************************/
  if ( Slave.waitRequest(20) )
  {
      digitalWrite(2, !Slave.relay.bits.b0 );
      digitalWrite(3, !Slave.relay.bits.b1 );
      digitalWrite(4, !Slave.relay.bits.b2 );
      digitalWrite(5, !Slave.relay.bits.b3 );
      digitalWrite(6, !Slave.relay.bits.b4 );
      digitalWrite(7, !Slave.relay.bits.b5 );
      digitalWrite(8, !Slave.relay.bits.b6 );
      digitalWrite(9, !Slave.relay.bits.b7 );
      
      /*
      Serial.println( "");
      Serial.print( "Relay" );
      Serial.print( i );
      Serial.print( ":" );
      Serial.print( Slave.relay[i] );
      */
    
    HaveTosend = true;
  }
  /*****************************************************************************/

  if (HaveTosend)
  {
    Slave.sendData();
  }
  delay(5);
};

