// Libreire richeiste;
// OneWIre
// DallasTemperature

#include <OneWire.h>
#include <DallasTemperature.h>

class CDallasProbe
{
    // GPIO where the DS18B20 is connected to
    int oneWireBus;

    // Setup a oneWire instance to communicate with any OneWire devices
    OneWire oneWire;

    // Pass our oneWire reference to Dallas Temperature sensor
    DallasTemperature sensors;

    double temperatureC;
    
  public:
    CDallasProbe(int gpio):
      oneWireBus(gpio),
      oneWire(oneWireBus),
      sensors(&oneWire)
    {};

    ~CDallasProbe() {};

    void setup( )
    {
      pinMode(oneWireBus, INPUT);
      sensors.begin();
    };

    void readvalues()
    {
      sensors.requestTemperatures(); 
      temperatureC = sensors.getTempCByIndex(0);
    };

    double GetTemperature()
    {
      return temperatureC;
    };
    
};
