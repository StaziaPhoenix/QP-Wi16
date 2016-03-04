#include "grid.h"
#include "controller.h"
//#include "vibsens.h"

/* shift register constants */
const int clockPin = 22;
const int latchPin = 23;
const int dataPin = 24;

/* delay times */
int staticDelay = 1;
int shockDelay = 30;
int moveDelay = 50;

/* flags */
int moveMode = 1; // 0 for static mode, 1 for move mode

/* Grid data */
int numCol = 10;
int numRow = 8;
int col[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
int colData[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int curs[2] = {1, 1};

/* sensor pins */
    // Joystick
int joyX = A3;
int joyY = A4;
    // Button
int button = 8;
    // Vibration
int vibrate;

grid matrix = grid(numCol, moveDelay);
controller joystick = controller(joyX, joyY, 0);

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

/* ------------------------------
 *  Set colData to the appropriate mode - 
 *  an LED for staticMode and the run for moveMode.
 *  Then call matAct the apropriate number of times for the mode.
 */
void loop() {
  
  /* call setData to prepare colData[] for the correct mode
   * Then read the updated colData into the local version. */
  if (moveMode) {
//    matrix.setData(moveMode);
//    for (int i = 0; i < numCol; i++) {
//      digitalWrite(col[i], LOW);
//      colData[i] = matrix.getData(i);
//    }
    colData[0] = 0x00;
    colData[1] = 0x02;
    moveLoop();
  }
}

void moveLoop() {
  for (int i = 0; i < numCol; i++) { // current column
    digitalWrite(col[i],HIGH);   

    /* check if we should switch mode. If yes, return to main loop */
//      if (digitalRead(button) == LOW)  {
//        moveMode = moveMode^1;
//        Serial.print("In staticLoop... ");
//        Serial.println(moveMode);
//        delay(300);
//        return;
//      }
    /* Adapt for joystick movements */
    checkJoystick();
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
    digitalWrite(latchPin,HIGH);
    delay(moveDelay);
    
    digitalWrite(col[i], LOW);
  }
}

void checkJoystick() {
  int orVal;

  switch(curs[0]) {
    case 0: orVal = 0x01; break;
    case 1: orVal = 0x02; break;
    case 2: orVal = 0x04; break;
  }
  if (joystick.moveLeft()) {
//    matrix.left(curs[0], curs[1]);
    if (curs[1] != 0) {
      colData[curs[1]-1] = colData[curs[1]-1] | orVal;
      Serial.println(colData[curs[1]-1]);
    }
    Serial.println("Left");
  }
//  if (joystick.moveRight()) {
//    matrix.right();
//    Serial.println("Right");
//  }
//  if (joystick.moveUp()) {
//    matrix.up();
//    Serial.println("Up");
//  }
//  if (joystick.moveDown()) {
//    matrix.down();
//    Serial.println("Down");
//  }
//  
//  for (int i = 0; i < numCol; i++) {
//    colData[i] = matrix.getData(i);
//  }
}

