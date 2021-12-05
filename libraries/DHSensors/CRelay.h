#ifndef crelay_h
#define crelay_h

#include "Arduino.h"

class CRelay
{
    int gpio_relay;
    int value;

  public:
    CRelay(int gpio):
      gpio_relay(gpio),
      value(0)
    {};

    ~CRelay() {};

    void setup( )
    {
     pinMode(gpio_relay, OUTPUT);
    }

    void writevalues()
    {
      digitalWrite(gpio_relay, !value);
    };

    int GetOnOff()
    {
      return value;
    };

    void set(int val)
    {
      value = val;
    };
};

#endif
