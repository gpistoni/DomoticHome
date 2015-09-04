#ifndef DHSdDb_h
#define DHSdDb_h

#include "Arduino.h"
#include <SD.h>

class DHSdDb
{
  public:
    String ReadValue( String section, String key);    
    void WriteValue( String section, String key, String value);    
};

#endif