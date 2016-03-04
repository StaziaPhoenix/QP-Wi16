#include "grid.h"
#include "controller.h"
//#include "vibsens.h"

/* shift register constants */
const int clockPin = 22;
const int latchPin = 23;
const int dataPin = 24;

/* delay times */
int moveDelay = 1;

/* flags */
int moveMode = 1; // 0 for auto sequences, 1 for move mode

/* grid data */
int numCol = 10;
int numRow = 8;
int col[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
int colData[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


/* sensors */
int joyX = A3;
int joyY = A4;
controller joystick = controller(joyX, joyY, 0);


void setup() {
  Serial.begin(9600);
  // Prepare shift registers
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 

  for (int i = 0; i < numCol; i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], LOW);
  }

  colData[0] = 0x01;

  initSeq();
}

void loop() {
  if (moveMode) {
    // hardcode init state for move mode

    moveLoop();
  }
}

void moveLoop() {
  static int cntr = 0;
  for (int i = 0; i < numCol; i++) {
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
    digitalWrite(latchPin,HIGH);

    digitalWrite(col[i], HIGH);
    delay(moveDelay);
    digitalWrite(col[i], LOW);
  }

  if (++cntr % 12 == 0) {
    checkJoystick();
  }
}

void checkJoystick() {
  static int curs[2] = {0, 0};
  int orVal;
  switch(curs[0]) {
    case 0: orVal = 0x01; break;
    case 1: orVal = 0x02; break;
    case 2: orVal = 0x04; break;
    case 3: orVal = 0x08; break;
    case 4: orVal = 0x10; break;
    case 5: orVal = 0x20; break;
    case 6: orVal = 0x40; break;
    case 7: orVal = 0x80; break;
    case 8: orVal = 0x01; break;
    case 9: orVal = 0x02; break;
    case 10: orVal = 0x04; break;
    case 11: orVal = 0x08; break;
  }

  int retVal;
  if (joystick.moveLeft()) {
    if (curs[1] != 0) {
      curs[1]--;
      colData[curs[1]] = colData[curs[1]] | orVal;
      Serial.println("Left");
      Serial.println(colData[curs[1]]);
    }
  }
  if (joystick.moveRight()) {
    if (curs[1] != (numCol-1)) {
      curs[1]++;
      colData[curs[1]] = colData[curs[1]] | orVal;
      Serial.println("Right");
      Serial.println(colData[curs[1]]);
    }
  }
  if (joystick.moveUp()) {
    if (curs[0] != 0) {
      curs[0]--;
      switch(curs[0]) {
        case 0: orVal = 0x01; break;
        case 1: orVal = 0x02; break;
        case 2: orVal = 0x04; break;
        case 3: orVal = 0x08; break;
        case 4: orVal = 0x10; break;
        case 5: orVal = 0x20; break;
        case 6: orVal = 0x40; break;
        case 7: orVal = 0x80; break;
        case 8: orVal = 0x01; break;
        case 9: orVal = 0x02; break;
        case 10: orVal = 0x04; break;
        case 11: orVal = 0x08; break;
      }
      colData[curs[1]] = colData[curs[1]] | orVal;
      Serial.println("Up");
    }
  }
    if (joystick.moveDown()) {
    if (curs[0] != numRow-1) {
      curs[0]++;
      switch(curs[0]) {
        case 0: orVal = 0x01; break;
        case 1: orVal = 0x02; break;
        case 2: orVal = 0x04; break;
        case 3: orVal = 0x08; break;
        case 4: orVal = 0x10; break;
        case 5: orVal = 0x20; break;
        case 6: orVal = 0x40; break;
        case 7: orVal = 0x80; break;
        case 8: orVal = 0x01; break;
        case 9: orVal = 0x02; break;
        case 10: orVal = 0x04; break;
        case 11: orVal = 0x08; break;
      }
      colData[curs[1]] = colData[curs[1]] | orVal;
      Serial.println("Down");
    }
  }
}

void initSeq() {
  for (int i = 0; i < numCol; i++) {         
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,0xFF);
    digitalWrite(latchPin,HIGH);
    
    digitalWrite(col[i],HIGH);
    delay(100);
    digitalWrite(col[i], LOW);
  }

  for (int j = 0; j < 30; j++) {
    for (int i = 0; i < numCol; i++) {         
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,0xFF);
      digitalWrite(latchPin,HIGH);
      
      digitalWrite(col[i],HIGH);
      delay(1);
      digitalWrite(col[i], LOW);
    }
  }
}

