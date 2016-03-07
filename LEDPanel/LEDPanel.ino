#include "grid.h"
#include "controller.h"
#include "vibsens.h"

/* shift register constants */
const int clockPin = 22;
const int latchPin = 23;
const int dataPin = 24;

const int clockPinB = 50; // IC Pin SH_CP, 11
const int latchPinB = 49; // IC Pin ST_CP, 12
const int dataPinB = 48; // IC pin DS, 14

/* delay times */
int moveDelay = 1;
int shockDelay = 20;

/* flags */
int moveMode = 1; // 0 for auto sequences, 1 for move mode

/* grid data */
int numCol = 10;
int numRow = 8;
int numRowB = 4;
int col[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
int colData[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int bDark[10] = {0xe, 0x8, 0x0, 0xe, 0xe, 0xa, 0x0, 0xe, 0xa, 0x4};
int logo[10] = { 0xf, 0x8, 0x8, 0x0, 0xf, 0xf, 0x0, 0x1, 0xf, 0x1 };


/* sensors */
int joyX = A3;
int joyY = A4;
controller joystick = controller(joyX, joyY, 0);
vibsens vibes = vibsens(29);
int button = 27;


void setup() {
  Serial.begin(9600);
  // Prepare shift registers
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 

  pinMode(latchPinB,OUTPUT);
  pinMode(dataPinB,OUTPUT);
  pinMode(clockPinB,OUTPUT);

  for (int i = 0; i < numCol; i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], LOW);
  }

  colData[0] = 0x01;

  initSeq();
}

/* Decide whether to be autonomous or 
 * interactive.
 */
void loop() {
  if (moveMode) {
    moveLoop();
  } else {
    if (patternRunning()) {
      return;
    }
    if (patternDiamonds()) {
      return;
    }
    if (patternDiag()) {
      return;
    }
  }
}

/* Manage interactive behavior. */
void moveLoop() {
  static int cntr = 0;
  for (int i = 0; i < numCol; i++) {
    digitalWrite(latchPin,LOW);
    digitalWrite(latchPinB,LOW);
    
    shiftOut(dataPinB,clockPinB,MSBFIRST, logo[i]);
    shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
    
    digitalWrite(latchPinB,HIGH);
    digitalWrite(latchPin,HIGH);

    digitalWrite(col[i], HIGH);
    delay(moveDelay);
    digitalWrite(col[i], LOW);
  }

  if (++cntr % 17 == 0) {
    checkJoystick();
  }
  checkVibsens();
  checkButton();
}

/* Turn on sequence for the matrix. 
 *  Indicates reset and power. */
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




/* ------------------------------------------
 *  Input check functions. Manages joystick, 
 *  vibration sensor, and pushbutton
 * ------------------------------------------ */

/* Controls paint mode, adjusting colData 
 * appropriately when the user moves the joystick. */
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

/* Check the vibration sensor and perform an 
 * interrupt sequence if positive */ 
void checkVibsens() {
  if (vibes.checkSens()) {
    for (int j = 0; j < 7; j++) {
      for (int i = 0; i < numCol; i++)
      {
        digitalWrite(col[i],HIGH);          
        digitalWrite(latchPin,LOW);
        shiftOut(dataPin,clockPin,MSBFIRST, vibes.vibrateRand());
        digitalWrite(latchPin,HIGH);
        delay(shockDelay);      
        digitalWrite(col[i], LOW);
      }
    }
  }
}

/* Check if we shoud switch modes. Return values 
 * is not always used, but helps autonomous sequences
 * escape back into moveLoop when requested. */
int checkButton() {
  if (digitalRead(button) == LOW)  {
    moveMode = moveMode^1;
    Serial.print("In staticLoop... ");
    Serial.println(moveMode);
    delay(300);
    return 1;
  }
  return 0;
}



/* ------------------------------------------
 *  Preset patterns. Cycle through during 
 *  autonomous mode.
 * ------------------------------------------ */
int patternRunning()
{
  int runn1[10] = {0x01, 0x01, 0x01, 0x01, 0x01,
                  0x01, 0x01, 0x01, 0x01, 0x01 };
  int runn2[10] = {0x11, 0x11, 0x11, 0x11, 0x11,
                  0x11, 0x11, 0x11, 0x11, 0x11 };
                  
  for (int j = 0; j < numRow; j++)
  {
    for (int i = 0; i < numCol; i++)
    {
      digitalWrite(latchPin,LOW);
      digitalWrite(latchPinB,LOW);
      
      shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
      shiftOut(dataPin,clockPin,MSBFIRST,runn1[i]);
      
      digitalWrite(latchPinB,HIGH);
      digitalWrite(latchPin,HIGH);
  
      digitalWrite(col[i], HIGH);
      delay(30);
      digitalWrite(col[i], LOW);
      
      runn1[i] = runn1[i] << 1;

      if (checkButton()) {
        return 1;
      }
    }
  }

  for (int j = 0; j < numRow; j++)
  {
    for (int i = 0; i < numCol; i++)
    {
      digitalWrite(latchPin,LOW);
      digitalWrite(latchPinB,LOW);
      
      shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
      shiftOut(dataPin,clockPin,MSBFIRST,runn2[i]);
      
      digitalWrite(latchPinB,HIGH);
      digitalWrite(latchPin,HIGH);
  
      digitalWrite(col[i], HIGH);
      delay(40);
      digitalWrite(col[i], LOW);
      
      runn2[i] = runn2[i] << 2 | runn2[i] >> 1 & 0xfe;

      if (checkButton()) {
        return 1;
      }
    }
  }
  return 0;
}

int patternDiamonds() {
  int di1[10] = {0x08, 0x14, 0x22, 0x14, 0x08, 0x08, 0x14, 0x22, 0x14, 0x08 };
  int di2[10] = {0x08, 0x1C, 0x36, 0x1C, 0x08, 0x08, 0x1C, 0x36, 0x1C, 0x08 };
  int di3[10] = {0x08, 0x1C, 0x3E, 0x1C, 0x08, 0x08, 0x1C, 0x3E, 0x1C, 0x08 };

  for (int k = 0; k < 3; k++) {
    for (int j = 0; j < 30; j++) {
      for (int i = 0; i < numCol; i++)
      {
        digitalWrite(latchPin,LOW);
        digitalWrite(latchPinB,LOW);
        
        shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
        shiftOut(dataPin,clockPin,MSBFIRST,di1[i]);
        
        digitalWrite(latchPinB,HIGH);
        digitalWrite(latchPin,HIGH);
    
        digitalWrite(col[i], HIGH);
        delay(1);
        digitalWrite(col[i], LOW);
  
        if (checkButton()) {
          return 1;
        }
      }
    }
  
    for (int j = 0; j < 40; j++) {
      for (int i = 0; i < numCol; i++)
      {
        digitalWrite(latchPin,LOW);
        digitalWrite(latchPinB,LOW);
        
        shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
        shiftOut(dataPin,clockPin,MSBFIRST,di2[i]);
        
        digitalWrite(latchPinB,HIGH);
        digitalWrite(latchPin,HIGH);
    
        digitalWrite(col[i], HIGH);
        delay(1);
        digitalWrite(col[i], LOW);
  
        if (checkButton()) {
          return 1;
        }
      }
    }
  
    for (int j = 0; j < 60; j++) {
      for (int i = 0; i < numCol; i++)
      {
        digitalWrite(latchPin,LOW);
        digitalWrite(latchPinB,LOW);
        
        shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
        shiftOut(dataPin,clockPin,MSBFIRST,di3[i]);
        
        digitalWrite(latchPinB,HIGH);
        digitalWrite(latchPin,HIGH);
    
        digitalWrite(col[i], HIGH);
        delay(1);
        digitalWrite(col[i], LOW);
  
        if (checkButton()) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int patternDiag()
{
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < numCol; i++)
    {
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPinB,LOW);
      if (i%2 == 0) 
      { 
        shiftOut(dataPin, clockPin, MSBFIRST, 0xAA);
        shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
      }
      else if (i%2 == 1)
      {
        shiftOut(dataPin, clockPin, MSBFIRST, 0x55);
        shiftOut(dataPinB,clockPinB,MSBFIRST, bDark[i]);
      }
      digitalWrite(latchPin, HIGH);
      digitalWrite(latchPinB,HIGH);
      digitalWrite(col[i], HIGH);
      delay(100);

      if (checkButton()) {
        return 1;
      }
    }
  }
  return 0;
}
