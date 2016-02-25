const int dataPin = 22; // IC pin DS, 14
const int clockPin = 24; // IC Pin SH_CP, 11
const int latchPin = 23; // IC Pin ST_CP, 12

byte numCols = 10;
byte numRows = 8;
byte sustain = 800;

unsigned short colData[10] = { 0x01, 0x01, 0x01, 0x01, 0x01,
                    0x01, 0x01, 0x01, 0x01, 0x01 };
unsigned short static1[10] = { 0x08, 0x14, 0x22, 0x14, 0x08,
                    0x08, 0x14, 0x22, 0x14, 0x08 };
unsigned short static2[10] = { 0x00, 0x08, 0x14, 0x08, 0x00,
                     0x00, 0x08, 0x14, 0x08, 0x00 };
unsigned short on[10] = { 0xff, 0xff, 0xff, 0xff, 0xff,
                    0xff, 0xff, 0xff, 0xff, 0xff };
byte cols[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};

void setup() {
  
  for( int i = 0; i < numCols; i++) {
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], LOW);
  }

  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);

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
      
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,on[i]);
      digitalWrite(latchPin,HIGH);
      delay(100);
  
      digitalWrite(cols[i], LOW);
    }
}

void loop() {
  for (int j = 0; j < sustain; j++) {
    for (int i = 0; i < numCols; i++) {
      digitalWrite(cols[i],HIGH);
      
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,static1[i]);
      digitalWrite(latchPin,HIGH);
      delay(1);
  
      digitalWrite(cols[i], LOW);
    }
  }
  for (int j = 0; j < sustain; j++) {
    for (int i = 0; i < numCols; i++) {
      digitalWrite(cols[i],HIGH);
      
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,static2[i]);
      digitalWrite(latchPin,HIGH);
      delay(1);
  
      digitalWrite(cols[i], LOW);
    }
  }
}


