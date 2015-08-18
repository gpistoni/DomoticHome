#include <DHT.h>
#include <RS485.h>
#include <ModbusSlave485.h>
#include <SPI.h>

#include "chdt.cpp"
#include "comslave.cpp"

CDht SensorsHDT;
CComSlave Slave;

void setup()
{
  SensorsHDT.setup(3, 4, 5);
  Slave.setup(2, 9600);

  Serial.begin(9600);
}

unsigned long old_ReadHDT = 0;
unsigned long old_Update = 0;
int reg[3];

void loop()
{
  unsigned long now = millis();

  //*****************************************************************************
  if ( now - old_ReadHDT >= 5000)
  {
    old_ReadHDT = now;

    SensorsHDT.readvalues();

    reg[0] = SensorsHDT.h[0] * 10;
    reg[1] = SensorsHDT.t[0] * 10;
    reg[2] = SensorsHDT.hic[0] * 10;

    reg[3] = SensorsHDT.h[1] * 10;
    reg[4] = SensorsHDT.t[1] * 10;
    reg[5] = SensorsHDT.hic[1] * 10;
  }
 //*****************************************************************************

    Slave.UpdateRegisters( reg, 6);
    delay(1000);
};
