#include <OneWire.h>
#include "cprobe.h"

void CProbe::setup( int in0, int in1, int in2, int in3, int in4, int in5, int in6, int in7)
{
  ds[0].setup(in0);
  if (in1) ds[1].setup( in1 );
  if (in2) ds[2].setup( in2 );
  if (in3) ds[3].setup( in3 );
  if (in4) ds[4].setup( in4 );
  if (in5) ds[5].setup( in5 );
  if (in6) ds[6].setup( in6 );
  if (in7) ds[7].setup( in7 );
  nums = 1 + (in1 != 0) + (in2 != 0) + (in3 != 0) + (in4 != 0) + (in5 != 0) + (in6 != 0) + (in7 != 0);
  for (int i = 0; i < 8; i++)
  {
    t[i] = 0;
  }
};

void CProbe::readvalues()
{
  for (int i = 0; i < nums; i++)
  {
    t[i] = _getTemp( i );
  }
}

float CProbe::_getTemp(int n) {
  //returns the temperature from one DS18S20 in DEG Celsius
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;

  if ( !ds[n].search(addr)) {
    //no more sensors on chain, reset search
    ds[n].reset_search();
    delay(50);
    return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1001;
  }

  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.print("\nChip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.print("\nChip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.print("\nChip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return -1002;
  }

  ds[n].reset();
  ds[n].select(addr);
  ds[n].write(0x44, 1); // start conversion, with parasite power on at the end

  delay(100);  //maybe ?

  byte present = ds[n].reset();
  ds[n].select(addr);
  ds[n].write(0xBE); // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for (int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds[n].read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }

  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  ds[n].reset_search();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];

  if (type_s) 
  {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } 
  else 
  {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;

  return celsius ;
}

