#ifndef cprobe_h
#define cprobe_h

/*   For Arduino 1.0 and newer, do this:   */
#include "Arduino.h"
#include <DHOneWire.h>

class CProbe
{
    DHOneWire  ds[8];

  public:
    int nums;
    double t[8];

CProbe(){};
~CProbe(){};

    void setup(int in0, int in1=0,int in2=0,int in3=0, int in4=0, int in5=0, int in6=0, int in7=0 );
    void readvalues();

private:
    float _getTemp(int i);
};

#endif
