// MODULO 06
// Amperometri
// scheda 6 SCt-013
// rev: 30 dic 2017
// rev 21 mar 2018
// rev 08 dic 2018

#define DISABLE_TRACE

#include <dhprotocol.h>
#include <cprobe.h>

#include "EmonLib.h"

#include <SoftwareSerial.h>

//#define _CHECK_TIME_
//static unsigned long last = 0; \
//if ( millis() - last < sec * 1000 ) return; \
//last = millis();

DHProtocol Slave;
SoftwareSerial mySerial(11, 12, TRUE);     // 11,12 Serial

#define NUM_SENS 5

EnergyMonitor emon[NUM_SENS];

double K[NUM_SENS] =  {
  35,           // 100A
  53,           // 30A
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

  Serial.begin(115200);
  Serial.print( "Setup-- SLAVE ID: " );
  Serial.print( Slave.m_id );

  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long old_ReadHDT = 0;
unsigned long read_t[8] = {millis(), millis(), millis(), millis(), millis(), millis(), millis(), millis()};

double totalwork[8] = {0, 0, 0, 0, 0, 0, 0, 0};
double totalElapsed[8] = {0, 0, 0, 0, 0, 0, 0, 0};

unsigned long rolling_i = 0;
const int V_rete = 233;

int pulse_cnt = 0;

static unsigned long last = 0;
static unsigned long last_pulse = 0;

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  if ( Slave.waitRequest( 40 ))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Slave.sendData();
  }

  if ( millis() - last > 500 )
  {
    last = millis();
    /*******************************************************************************/
    unsigned long now = millis();               // Terminal ID

    int i = rolling_i++ % NUM_SENS;
    int elapsed = millis() - read_t[i] ;
    read_t[i] = millis();

    double Irms = emon[i].calcIrms(1480);

    if ( Irms < 0.20 ) Irms = 0.0;
    double work = Irms * V_rete * elapsed / 1000.0 / 3600.0;

    totalwork[i] += work;
    totalElapsed[i] += elapsed / 1000.0;

    Slave.sensor[i] = (int)( Slave.sensor[i] * 0.8 + (Irms * V_rete * 10.0) * 0.2); // watt
    Slave.sensor[8 + i] = (int)( Slave.sensor[8 + i] * 0.8 + (totalwork[i] / 1000.0 * 10.0) * 0.2);
    Slave.sensor[16 + i] = (int)(Slave.sensor[16 + i] * 0.8 + (totalElapsed[i] / 3600.0 * 10.0) * 0.2 );

    if (rolling_i < 100 )
    {
      Serial.println("");
      Serial.print(" K: ");
      Serial.print(K[i]); // Irms

      Serial.print("\t (W) : ");
      Serial.print( Slave.sensor[i] / 10.0 ); //Scrivo sul monitor seriale Corrente*Tensione=Potenza
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

  //Sensor 6 *********************************************************************
  int sensorValue = analogRead(A6);
  unsigned long dt = millis() - last_pulse;
  if ( sensorValue > 100 && dt > 1000)
  {
    float sec = dt / 1000.0;
    float wPulse = 3600 / sec * 10;

    Slave.sensor[6] = wPulse;

    pulse_cnt++;
    last_pulse =  millis();

    Serial.print(" Pulse dt: ");
    Serial.print(dt);
    Serial.print(" W: ");
    Serial.println(wPulse);
  }

  if (dt > 200000)
  {
    Slave.sensor[6] = 0;
  }
  /*****************************************************************************/
};
