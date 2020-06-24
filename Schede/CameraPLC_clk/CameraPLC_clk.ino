#include <Arduino.h>
#include <Ticker.h>

#define DIV512(i)    (i)>>9
#define DIV1024(i)   (i)>>10
#define DIV2048(i)   (i)>>11

#define DIV2048_BIT0(i)   (((i)>>11) & 0x1)
#define DIV4096_BIT0(i)   (((i)>>12) & 0x1)

const unsigned long MASTER_FREQ = 2000;
const unsigned long interval_us = 1000 * 1000 / MASTER_FREQ;
const unsigned long interval_tick = 5 * interval_us;

volatile unsigned long clock_encoder = 0;

int ENCODER1 = D0;
int ENCODER2 = D1;

int LIGHT = D2;
int INPUT1 = D7;

volatile unsigned long MASTER_CLOCK;
// ISR to Fire when Timer is triggered
void ICACHE_RAM_ATTR onTime()
{
  MASTER_CLOCK++;
  //  Serial.print("Total Ticks:");
  //  Serial.println(MASTER_CLOCK);
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ENCODER1, OUTPUT);
  pinMode(ENCODER2, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(INPUT1, INPUT);

  //attachInterrupt(INPUT1, interrupt_SendMessage, RISING);

  //Initialize Ticker
  timer1_attachInterrupt(onTime);       // Add ISR Function
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  /* Dividers:
    TIM_DIV1 = 0,   //80MHz (80 ticks/us - 104857.588 us max)
    TIM_DIV16 = 1,  //5MHz (5 ticks/us - 1677721.4 us max)
    TIM_DIV256 = 3  //312.5Khz (1 tick = 3.2us - 26843542.4 us max)
    Reloads:
    TIM_SINGLE  0 //on interrupt routine you need to write a new value to start the timer again
    TIM_LOOP  1 //on interrupt the counter will start with the same value again
  */

  timer1_write(interval_tick);
  //END Initialize Ticker
  
  // Start server
  Serial.println("READY");
}

void SendEncoder()
{
  static unsigned long oldCrono = millis();
  static unsigned long oldMasterClock = 0;
  if (MASTER_CLOCK != oldMasterClock )
  {
    int value = MASTER_CLOCK % 2;
    digitalWrite(ENCODER1, value);
    digitalWrite(ENCODER2, !value);

    oldMasterClock = MASTER_CLOCK;
    digitalWrite(LED_BUILTIN, (MASTER_CLOCK / 1000 % 2)); // 1Hz

    if (value)
    {
      clock_encoder++;
      if (clock_encoder % 1000 == 0)
      {
        Serial.print("1000 clock in (ms):");
        Serial.println(millis() - oldCrono);
        oldCrono = millis();
      }
    }
  }
}

void Light()
{
  int LightStatus = DIV4096_BIT0(clock_encoder); //(clock_encoder/2048 % 2);
  static unsigned long oldLightStatus = 0;
  if (LightStatus!= oldLightStatus)
  {  
    digitalWrite(LIGHT, LightStatus);    
    oldLightStatus =LightStatus; 
  }
}

void loop()
{
  SendEncoder();
  Light();
}
