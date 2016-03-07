#include "Arduino.h"
#include "vibsens.h"
#include "grid.h" 
#include "stdlib.h"

vibsens::vibsens(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin; 
}
int vibsens::checkSens()
{
  if (digitalRead(_pin) == LOW)
  {
    delay(50);
    if (digitalRead(_pin) == HIGH)
    {
      return 1; 
    }
  }
  return 0; 
}
int vibsens::vibrateRand()
{
  int rand1 = rand();
  return (rand1%256);
}
int vibsens::rawRead()
{
  return digitalRead(_pin);
}

