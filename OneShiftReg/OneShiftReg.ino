const int dataPinT = 22; // IC pin DS, 14
const int clockPinT = 24; // IC Pin SH_CP, 11
const int latchPinT = 23; // IC Pin ST_CP, 12

const int dataPinB = 26; // IC pin DS, 14
const int clockPinB = 28; // IC Pin SH_CP, 11
const int latchPinB = 27; // IC Pin ST_CP, 12

byte numCols = 10;
byte numRowsT = 8;
byte numRowsB = 4;
byte sustain = 800;

unsigned short colDataT[10] = { 0x01, 0x01, 0x01, 0x01, 0x01,
                    0x01, 0x01, 0x01, 0x01, 0x01 };
unsigned short colDataB[10] = { 0x01, 0x01, 0x01, 0x01, 0x01,
                    0x01, 0x01, 0x01, 0x01, 0x01 };
                    
unsigned short static1[10] = { 0x08, 0x14, 0x22, 0x14, 0x08,
                    0x08, 0x14, 0x22, 0x14, 0x08 };
unsigned short static2[10] = { 0x00, 0x08, 0x14, 0x08, 0x00,
                     0x00, 0x08, 0x14, 0x08, 0x00 };
                     
unsigned short on1[10] = { 0xff, 0xff, 0xff, 0xff, 0xff,
                    0xff, 0xff, 0xff, 0xff, 0xff };
unsigned short on2[10] = { 0xff, 0xff, 0xff, 0xff, 0xff,
                    0xff, 0xff, 0xff, 0xff, 0xff };
byte cols[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};

void setup() {
  
  for( int i = 0; i < numCols; i++) {
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], LOW);
  }

  pinMode(latchPinT,OUTPUT);
  pinMode(dataPinT,OUTPUT);
  pinMode(clockPinT,OUTPUT);

  pinMode(latchPinB,OUTPUT);
  pinMode(dataPinB,OUTPUT);
  pinMode(clockPinB,OUTPUT);

  delay(2000);
//  for (int j = 0; j < numRows; j++) {
//    for (int i = 0; i < numCols; i++) {
//      digitalWrite(cols[i],HIGH);
//      
//      digitalWrite(latchPin,LOW);
//      shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
//      digitalWrite(latchPin,HIGH);
//      delay(100);
//  
//      digitalWrite(cols[i], LOW);
//      colData[i] = colData[i] << 1;
//    }
//  }
    for (int i = 0; i < numCols; i++) {
      digitalWrite(cols[i],HIGH);
      
      digitalWrite(latchPinT,LOW);
      digitalWrite(latchPinB,LOW);
      shiftOut(dataPinT,clockPinT,MSBFIRST,on1[i]);
      shiftOut(dataPinB,clockPinB,MSBFIRST,on2[i]);
      digitalWrite(latchPinT,HIGH);
      digitalWrite(latchPinB,HIGH);
      delay(100);
  
      digitalWrite(cols[i], LOW);
    }
}

void loop() {
//  for (int j = 0; j < sustain; j++) {
//    for (int i = 0; i < numCols; i++) {
//      digitalWrite(cols[i],HIGH);
//      
//      digitalWrite(latchPinT,LOW);
//      shiftOut(dataPinT,clockPinT,MSBFIRST,static1[i]);
//      digitalWrite(latchPinT,HIGH);
//      delay(1);
//  
//      digitalWrite(cols[i], LOW);
//    }
//  }
    for (int i = 0; i < numCols; i++) {
      digitalWrite(cols[i],HIGH);
      
      digitalWrite(latchPinT,LOW);
      digitalWrite(latchPinB,LOW);
      shiftOut(dataPinT,clockPinT,MSBFIRST,on1[i]);
      shiftOut(dataPinB,clockPinB,MSBFIRST,on2[i]);
      digitalWrite(latchPinT,HIGH);
      digitalWrite(latchPinB,HIGH);
      delay(100);
  
      digitalWrite(cols[i], LOW);
    }
}


