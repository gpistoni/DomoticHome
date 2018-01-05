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

#define NUM_SENS 5

EnergyMonitor emon[6];
int V_rete = 233.0;

double K[6] =  {
  31.5,           // 100A
  50.2,           // 30A
  40,             // 15A
  40,             // 15A
  40,             // 15A
  29  
};


void setup()
{
  Slave.setup(6, 0, &mySerial);     // Terminal ID

  //Pin, calibrazione - Corrente Const= Ratio/Res. Burder. 1800/62 = 29.
  emon[0].current(A0, K[0]);
  emon[1].current(A1, K[1]);
  emon[2].current(A2, K[2]);
  emon[3].current(A3, K[3]);
  emon[4].current(A4, K[4]);
  emon[5].current(A5, K[5]);

  Serial.begin(9600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );

  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long old_ReadHDT = 0;
double totalwork=0;

void loop()
{
  digitalWrite(LED_BUILTIN, LOW); 
  if ( Slave.waitRequest( 50 ) )
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Slave.sendData();
  }

  /*******************************************************************************/
  unsigned long now = millis();               // Terminal ID
  unsigned long elapsed = now - old_ReadHDT;  // Elapsed

  if ( elapsed >= 5000)             // leggo probe ogni 2 secondi
  {
    old_ReadHDT = now;

    Serial.println( "Readvalues" );
    for ( int i = 0; i < NUM_SENS; i++)
    {
      double Irms = emon[i].calcIrms(1480);
      double Pow = Irms * V_rete;
      double Work = Pow * elapsed / 1000 / 3600;

      totalwork+= Work;

      Slave.sensor[i] = Irms * 10;
      Slave.sensor[8 + i] = Pow;
      Slave.sensor[16 + i] = totalwork;

      Serial.print(i);
      Serial.print(" K: ");
      Serial.print(K[i]); // Irms

      Serial.print(" Corrente (A): ");
      Serial.print(Slave.sensor[i] / 10.0 ); // Irms

      Serial.print(" Potenza (w) : ");
      Serial.print(Slave.sensor[8 + i]); //Scrivo sul monitor seriale Corrente*Tensione=Potenza

      Serial.print(" Lavoro (wh) : ");
      Serial.print( Work ); // Scrivo sul monitor seriale Corrente*Tensione=Potenza
      Serial.print(" total (wh) : ");
      Serial.println( totalwork ); // Scrivo sul monitor seriale Corrente*Tensione=Potenza
    }
  }

  /*****************************************************************************/
};


