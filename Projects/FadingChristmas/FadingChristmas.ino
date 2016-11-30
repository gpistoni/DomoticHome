int ledPin = 10;    // LED connected to digital pin 9

void setup()
{
  // nothing happens in setup
}

void loop()
{
  for (int fadeValue=0 ; fadeValue<=12; fadeValue+=1 )
  {
    analogWrite(ledPin, fadeValue*fadeValue);
    delay(50);
  }

  for (int c = 0 ; c <= 3; c++ )
  {
    analogWrite(ledPin, 200);
    delay(100);
    analogWrite(ledPin, 64);
    delay(100);
  }
   analogWrite(ledPin, 200);
   
  for (int fadeValue=120 ; fadeValue>=0; fadeValue-=10 )
  {
    analogWrite(ledPin, fadeValue);
    delay(50);
  }
}


