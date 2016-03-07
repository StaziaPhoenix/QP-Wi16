#include "grid.h"
//#include "controller.h"
#include "vibsens.h"

/* shift register constants */
const int latchPin = 13;
const int clockPin = 11;
const int dataPin = 9;

//vibration sens 
vibsens sens = vibsens(8);
/* delay times */
int staticDelay = 1;
int shockDelay = 30;
int moveDelay = 100;

/* flags */
int moveMode = 1; // 0 for static mode, 1 for move mode

/* Grid data */
int numCol = 5;
int numRow = 5;
int col[5] = {2, 3, 4, 5, 6};
int colData[5];

grid matrix = grid(numCol, moveDelay);

/* sensor pins */
    // Joystick
int joyX = A3;
int joyY = A4;
    // Button
int button = 8;
    // Vibration
int vibrate;

void setup() {
  Serial.begin(9600);
  
  // Prepare shift registers
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 

  // initialize outputs and column data
  matrix.setData(moveMode);
  for (int i = 0; i < numCol; i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], LOW);
    colData[i] = matrix.getData(i);
  }

  // run the initialization sequence
  for (int i = 0; i < numCol; i++) {
    digitalWrite(col[i],HIGH);          
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,0xFF);
    digitalWrite(latchPin,HIGH);
    delay(moveDelay);
    
    digitalWrite(col[i], LOW); 
  }

  delay(300);
}

void loop() {
//      Serial.print("In loop... ");
//      Serial.println(moveMode);
//  // call set data to prepare colData[] for the correct mode
//  // Then read the updated colData into the local version.
//  matrix.setData(moveMode);
//  for (int i = 0; i < numCol; i++) {
//    digitalWrite(col[i], LOW);
//    colData[i] = matrix.getData(i);
//  }
//  
//  if (moveMode) {
//    moveLoop();
//  } else {
//    staticLoop();
//  }
  Serial.println(sens.rawRead());
  if(sens.checkSens()) 
  {
    for (int z = 0; z < 2; z++)
    {
      for (int i = 0; i < numCol; i++)
      {
        digitalWrite(col[i],HIGH);          
        digitalWrite(latchPin,LOW);
        shiftOut(dataPin,clockPin,MSBFIRST, sens.vibrateRand());
        digitalWrite(latchPin,HIGH);
        delay(shockDelay);      
        digitalWrite(col[i], LOW);
      }
    }
  }
  /*
  int shockData1[5] = {0x1f, 0x19, 0x1F, 0x11, 0x1f};
  int shockData2[5] = {0x11, 0x1f, 0x19, 0x1f, 0x11};
  for (int i = 0; i < numCol; i++) {
    digitalWrite(col[i],HIGH);          
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,shockData1[i]);
    digitalWrite(latchPin,HIGH);
    delay(shockDelay);
    
    digitalWrite(col[i], LOW); 
  }
  for (int i = 0; i < numCol; i++) {
    digitalWrite(col[i],HIGH);          
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,shockData2[i]);
    digitalWrite(latchPin,HIGH);
    delay(shockDelay);
    
    digitalWrite(col[i], LOW); 
  }
  */
}

/* -------------------------
 *  Constant behavior while in static mode
 * ----------------------- 
void staticLoop() {
  // check if we should switch mode. If yes, return to main loop  
  for (int i = 0; i < numCol; i++) {
    digitalWrite(col[i],HIGH);   
     
    if (digitalRead(button) == LOW)  {
      moveMode = moveMode^1;
      Serial.print("In staticLoop... ");
      Serial.println(moveMode);
      delay(300);
      return;
    }   
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
    digitalWrite(latchPin,HIGH);
    delay(0);
    
    digitalWrite(col[i], LOW); 
  }
}
*/
/* -------------------------
 *  Constant behavior while in move mode
 * ----------------------- 
void moveLoop() {
  for (int i = 0; i < numRow; i++) { // current row
    for (int j = 0; j < numCol; j++) { // current column
      digitalWrite(col[j], HIGH);   
      
      // check if we should switch mode. If yes, return to main loop
      if (digitalRead(button) == LOW)  {
        moveMode = moveMode^1; 
        Serial.print("In moveLoop... ");
        Serial.println(moveMode);
        delay(300);
        return;
      }
     
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colData[j]);
      digitalWrite(latchPin,HIGH);
      delay(moveDelay);
      
      digitalWrite(col[j], LOW); 

      colData[j] = colData[j] << 1;
    }
  }
}
*/
