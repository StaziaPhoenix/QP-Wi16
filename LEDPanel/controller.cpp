 #include "Arduino.h"
 #include "controller.h"

controller::controller(int x, int y, int z)
{
  xPin = x;
  yPin = y;
  zPin = z; 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);
}


int controller::moveRight()
{
  int xR = analogRead(xPin);
  if (xR < 300 && xR >=0) 
  {
    return 1; 

  }
  return 0;
}
int controller::moveLeft()
{
  int xR = analogRead(xPin);
  if (xR > 800 && xR <= 1023)
  {
    return 1;       
  }
  return 0;
}
int controller::moveUp()
{
  int yR = analogRead(yPin);
  if (yR > 800 && yR <=1023)
    return 1;
  return 0; 
}
int controller::moveDown()
{
  int yR = analogRead(yPin);
  if (yR < 300 && yR >= 0)
    return 1;
  return 0; 
}

int controller::zMode()
{
  if (analogRead(zPin == LOW))
  {
    //pulse
  }
}

