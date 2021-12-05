// Libreire richeiste;
// OneWIre
// DallasTemperature

#include <OneWire.h>
#include <DallasTemperature.h>

class CDallasProbe
{
    // Setup a oneWire instance to communicate with any OneWire devices
    OneWire oneWire;

    // Pass our oneWire reference to Dallas Temperature sensor
    DallasTemperature sensors;

    double temperatureC;
    
  public:
    CDallasProbe(int gpio):
      oneWire(gpio),
      sensors(&oneWire)
    {};

    ~CDallasProbe() {};

    void setup( )
    {
      sensors.begin();
      
      int nTs = sensors.getDeviceCount();
      Serial.println("Dallas Sensor Found:"  + String(nTs) );  
      
      byte addr[8];
       if (!oneWire.search(addr)) 
      	{
    		Serial.println(" No more addresses.");
	    	Serial.println();
	    	oneWire.reset_search();
	    	delay(250);
	}      
	else
	{
		for (int i = 0; i < 8; i++) 
		{
		    Serial.write(' ');
		    Serial.print(addr[i], HEX);
	 	}
        Serial.println(" ");
	}	 
    };

    void readvalues()
    {
      //portDISABLE_INTERRUPTS();
      sensors.requestTemperatures(); 
      delay(1000);
      
      const unsigned int num_DS18B20 = sensors.getDeviceCount();
      Serial.println("Devices: " + String(num_DS18B20) );
      
      temperatureC = sensors.getTempCByIndex(0);
      Serial.println("Temp: " + String(temperatureC) );  
      //portENABLE_INTERRUPTS();
    };

    double GetTemperature()
    {
      return temperatureC;
    };
    
};
