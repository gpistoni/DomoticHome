#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include "screen.h"

CScreen disp;

ButtonLabel lkg, vkg;

void setup(void)
{
  Serial.begin(9600);
  tft.reset();

  // put your setup code here, to run once:
  disp.setup();

  vkg.setup(20, 70, 140, 100, "0.0", CYAN);
  lkg.setup(162, 70, 60, 100, "Kg", CYAN);
}

float analogToLoad(float analogval, float zero)
{
  return (analogval - zero) * 25;
}

void loop()
{
  static long zerotime = millis();
  static long time = 0;
  static float analogValueAverage = 0;
  static float zero = 0;

  TSPoint p = disp.getTouchPoint();

  if ( lkg.pressed(p) )
  {
    vkg.label( "-" );
    vkg.bkgCol( CYAN );
    zerotime = millis();
  }

  int analogValue = analogRead(A5);
  analogValueAverage = 0.99 * analogValueAverage + 0.01 * analogValue;

  if (zero == 0 && millis() > zerotime + 2000)
  {
    zero = analogValueAverage;
  }
  if ( millis() > time + 200)
  {
    float kg = analogToLoad( analogValueAverage, zero ) / 1000.0;

    Serial.print("Analog: ");
    Serial.print(analogValueAverage);
    Serial.print(" Kg: ");
    Serial.print( kg );

    vkg.label( kg, 5, 1);
    time = millis();
  }
}

