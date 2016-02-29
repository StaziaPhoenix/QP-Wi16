#include "vibsens.h"

vibsens::vibsens(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin; 
}

void vibsens::slowFreq()
{
  delay(50);
}

