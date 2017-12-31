// MODULO 06
// Amperometri
// scheda 6 SCt-013
// rev: 30 dic 2017

#include <dhprotocol.h>
#include <cprobe.h>

#include "EmonLib.h"

#include <SoftwareSerial.h>

DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial

#define NUM_SENS 4

EnergyMonitor emon[6];
int rede = 230.0;

void setup()
{
  Slave.setup(6, 0, &mySerial);     // Terminal ID

  //Pin, calibrazione - Corrente Const= Ratio/Res. Burder. 1800/62 = 29.
  emon[0].current(A0, 29);
  emon[1].current(A1, 29);
  emon[2].current(A2, 29);
  emon[3].current(A3, 29);
  emon[4].current(A4, 29);
  emon[5].current(A5, 29);

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

    Serial.println( "Readvalues" );
    for ( int i = 0; i < NUM_SENS; i++)
    {
      double Irms = emon[i].calcIrms(1480);      
      Slave.sensor[i] = Irms;
      double Pow = Irms*rede;
    
      Slave.sensor[8 + i] = Slave.sensor[8 + i];
      Slave.sensor[16 + i] = Slave.sensor[16 + i];

      Serial.print(i);
      Serial.print(" Corrente (A): ");
      Serial.print(Irms); // Irms

      Serial.print(" Potenza (w) : ");
      Serial.println(Irms*rede);//Scrivo sul monitor seriale Corrente*Tensione=Potenza
 
    }
  }

  /*****************************************************************************/
};


