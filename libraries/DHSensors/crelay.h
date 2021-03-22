#ifndef crelay_h
#define crelay_h

#include "Arduino.h"

class CRelay
{
    int gpio_relay[8];
    int relay[8];
	
public:
    CRelay(){};
    ~CRelay(){};

    void setup(int in0, int in1=0,int in2=0,int in3=0, int in4=0, int in5=0, int in6=0, int in7=0 );
    
    void writeOutput();    
    int getOnOff(int i){ if (i<8) return relay[i]; return 0;};
    void set(int i, int value) { if (i<8) relay[i] = value;}; 

private:
    float _getTemp(int i);
};

#endif
