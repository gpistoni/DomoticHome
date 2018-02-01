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

#define NUM_SENS 6

EnergyMonitor emon[6];

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

  Serial.begin(115200);
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
  if ( Slave.waitRequest( 50 ) )
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

    double Irms = emon[i].calcIrms(1480);
    double work = Irms * V_rete * elapsed / 1000 / 3600.0;

    totalwork[i] += work;
    totalElapsed[i] += elapsed;

    Slave.sensor[i] = Irms * 10.0;
    Slave.sensor[8 + i] = totalwork[i];
    Slave.sensor[16 + i] = totalElapsed[i];

    if (i == 0) Serial.print("\n");
    Serial.print("\n");
    Serial.print(i);
    Serial.print(" K: ");
    Serial.print(K[i]); // Irms

    Serial.print("\t (A): ");
    Serial.print(Slave.sensor[i] / 10.0); // Irms
    Serial.print("\t (W) : ");
    Serial.print(Slave.sensor[i] * V_rete / 10); //Scrivo sul monitor seriale Corrente*Tensione=Potenza

    Serial.print("\t Lavoro (wh) : ");
    Serial.print( work ); // Scrivo sul monitor seriale Corrente*Tensione=Potenza
    Serial.print("\t Totale (wh) : ");
    Serial.print( totalwork[i] ); // Scrivo sul monitor seriale kwh
    Serial.print(" in (s) : ");
    Serial.print( totalElapsed[i] / 1000 ); // Scrivo sul monitor seriale kwh

  }
  /*****************************************************************************/
};


