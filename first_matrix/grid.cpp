#include "grid.h"
#include "vibsens.h" 

grid::grid(int col), int dlay)
{
  numCol = col; 
  delay = dlay;
  col[numCol];
  colInit[numCol]; 
  for (int i =0; i < numCol; i++)
  {
    col[i] = 0;
  }
  for (int i = 0; i < numCol; i++)
  {
    colInit[i] = 0xFF;
  }
  pinMode(col0, OUTPUT);
  pinMode(col1, OUTPUT); 
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT); 
  vibsens vibe = vibsens(
}
void grid::defState()
{
  for (int i = 0; i < numCol; i++)
  {
   for (int j = 0; j < numCol; j++)
   {
      if (digitalRead(toggle) == LOW) 
      {
        modeFlag = modeFlag^1; 
        setData();
        j= 0;
        i =0;
      }
      digitalWrite(cols[i],HIGH);          
      digitalWrite(cols[i],HIGH);
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
      digitalWrite(latchPin,HIGH);
      delay(100);
      digitalWrite(cols[i], LOW); 
      adjustData(i);
   }
  }
}
void grid::adjustData(int i) 
{
  if (!modeFlag) {
     colData[i] = colData[i] << 1;
  }
}



