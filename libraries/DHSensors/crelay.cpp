#include "crelay.h"

void CRelay::setup( int in0, int in1, int in2, int in3, int in4, int in5, int in6, int in7)
{
  gpio_relay[0]=in0;
  gpio_relay[1]=in1;
  gpio_relay[2]=in2;
  gpio_relay[3]=in3;
  gpio_relay[4]=in4;
  gpio_relay[5]=in5;
  gpio_relay[6]=in6;
  gpio_relay[7]=in7;
  for (int i = 0; i < 8; i++) relay[i] = 0;  
  writeOutput();
};

void CRelay::writeOutput()
{
  for (int i = 0; i < 8; i++)
  {
     digitalWrite(gpio_relay[i], !relay[i]);
  }
}


