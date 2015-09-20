#ifndef chdt_h
#define chdt_h

/*   For Arduino 1.0 and newer, do this:   */
#include "Arduino.h"
#include <DHT.h>

class CDht
{
  private:
    DHT dht[10];

  public:
    int nums;

    double h[10];
    double t[10];
    double hic[10];

  public:
    void setup(int in0, int in1=0,int in2=0,int in3=0, int in4=0, int in5=0, int in6=0, int in7=0, int in8=0 );
    void readvalues();
};

#endif

