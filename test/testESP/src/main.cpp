#include <Arduino.h>


const int ACT = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(ACT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(ACT, 1);
    delay(1000);
     digitalWrite(ACT, 0);
       delay(1000);
}