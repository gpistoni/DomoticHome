// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include <Joystick.h>

void setup() 
{
  // Initialize Button Pins
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
  Serial.begin(9600);
}

int sensorPin = A0;
// Last state of the button
int lastButtonState[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void loop() 
{
  // Read PIN values
  for (int index = 0; index < 14 ; index++)
  {
    int currentButtonState = !digitalRead(index);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
      Serial.print("button");
      Serial.println(index);
    }
  }
  
  // Read ANALOG values
  int  sensorValue = analogRead(sensorPin);
  sensorValue -= 511;
  sensorValue /= 4;
  Joystick.setZAxis(sensorValue);

  delay(1);
}

