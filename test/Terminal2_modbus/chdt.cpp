#include <DHT.h>

class CDht
{
  private:
    DHT dht[8];

  public:
    int nums;

    double h[8];
    double t[8];
    double hic[8];

  public:
    void setup(int in1,int in2=0,int in3=0, int in4=0, int in5=0, int in6=0, int in7=0 )
    {
      dht[0].setup( in1, DHT21);
      if (in2) dht[1].setup( in2, DHT21);
      if (in3) dht[1].setup( in3, DHT21);
      if (in4) dht[1].setup( in4, DHT21);
      if (in5) dht[1].setup( in5, DHT21);
      if (in6) dht[1].setup( in6, DHT21);
      if (in7) dht[1].setup( in7, DHT21);
      nums = 1 + (in2!=0) + (in3!=0)+ (in4!=0) + (in5!=0) + (in6!=0) + (in7!=0);
      
      for (int i = 0; i < nums; i++)
        dht[i].begin();
    };

    void readvalues()
    {
      for (int i = 0; i < nums; i++)
      {
        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        h[i] = 0;
        h[i] = dht[i].readHumidity();
        // Read temperature as Celsius (the default)
        t[i] = 0;
        t[i] = dht[i].readTemperature();

        // Check if any reads failed and exit early (to try again).
        if (isnan(h[i]) || isnan(t[i]) )
        {
          continue;
        }
        // Compute heat index in Fahrenheit (the default)
        hic[i] = dht[i].computeHeatIndex(t[i], h[i], false);
      };
    };
};

