int ledPin = 10;    // LED connected to digital pin 9

void setup()
{
  // nothing happens in setup
}

int nc = 0;

void loop()
{
  nc++;
  nc = nc % 3;

  for (int fadeValue = 3 ; fadeValue <= 128; fadeValue += 1 )
  {
    analogWrite(ledPin, fadeValue);
    delay(30);
  }

  for (int c = 0 ; c <= nc; c++ )
  {
    analogWrite(ledPin, 255);
    delay(100);
    analogWrite(ledPin, 64);
    delay(50);
  }

  for (int fadeValue = 128 ; fadeValue >= 3; fadeValue -= 1 )
  {
    analogWrite(ledPin, fadeValue);
    delay(30);
  }
}


