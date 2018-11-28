// MODULO 06
// Amperometri
// scheda 6 SCt-013
// rev: 30 dic 2017
// rev 21 mar 2018

#include <dhprotocol.h>
#include <cprobe.h>

#include "EmonLib.h"

#include <SoftwareSerial.h>

DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial

#define NUM_SENS 5

EnergyMonitor emon[6];

double K[6] =  {
  32,           // 100A
  53,           // 30A
  40,
  40,           // 15A
  40,           // 15A
  40            // 15A
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

  Serial.begin(57600);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );

  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long old_ReadHDT = 0;

unsigned long read_t[8] = {millis(), millis(), millis(), millis(), millis(), millis(), millis(), millis()};

double totalwork[8] = {0, 0, 0, 0, 0, 0, 0, 0};
double totalElapsed[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int rolling_i = 0;
const int V_rete = 233;

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  if ( Slave.waitRequest( 40 ) )
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Slave.sendData();
  }
  else
  {
    /*******************************************************************************/
    unsigned long now = millis();               // Terminal ID

    int i = rolling_i++ % NUM_SENS;
    int elapsed = millis() - read_t[i] ;
    read_t[i] = millis();

    double v = analogRead(A0);

    double Irms = emon[i].calcIrms(1480);
    
    if ( Irms < 0.10 ) Irms = 0.0;
    double work = Irms * V_rete * elapsed / 1000.0 / 3600.0;

    totalwork[i] += work;
    totalElapsed[i] += elapsed / 1000.0;

    Slave.sensor[i] = (int)(Irms * V_rete) * 10.0; // watt
    Slave.sensor[8 + i] = (int)(totalwork[i] / 1000.0);
    Slave.sensor[16 + i] = (int)(totalElapsed[i] / 60.0 / 60.0);

    if (i == 0 && rolling_i < 1000 )
    {
      Serial.print("\n");
      Serial.print(v);
      Serial.print(" K: ");
      Serial.print(K[i]); // Irms

      Serial.print("\t (W) : ");
      Serial.print( Slave.sensor[i]/10.0 ); //Scrivo sul monitor seriale Corrente*Tensione=Potenza
      Serial.print("\t (wh) : ");
      Serial.print( work ); // Scrivo sul monitor seriale Corrente*Tensione=Potenza
      Serial.print("\t Totale (wh) : ");
      Serial.print( totalwork[i] ); // Scrivo sul monitor seriale kwh
      Serial.print("\t (Kwh) : ");
      Serial.print( Slave.sensor[8 + i] );
      Serial.print(" in (s) : ");
      Serial.print( totalElapsed[i] ); // Scrivo sul monitor seriale kwh
      Serial.print(" (h) : ");
      Serial.print( Slave.sensor[16 + i] );
    }
  }
  /*****************************************************************************/
};
