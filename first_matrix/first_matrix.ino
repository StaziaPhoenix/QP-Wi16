//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 22;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 23;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 24;

byte col0 = 30;
byte col1 = 31;
byte col2 = 32;
byte col3 = 33;
byte col4 = 34;

//
//byte row0 = 22;
//byte row1 = 25;
//byte row2 = 26;

byte colData[5] = {0xFf, 0xFf, 0xFC, 0xFC, 0xFC};
byte cols[5] = {col0, col1, col2, col3, col4};

void setup() {
  pinMode(col0,OUTPUT);
  pinMode(col1,OUTPUT);
  pinMode(col2,OUTPUT);
  pinMode(col3,OUTPUT);
  pinMode(col4,OUTPUT);

  digitalWrite(col0,LOW);
  digitalWrite(col1,LOW);
  digitalWrite(col2,LOW);
  digitalWrite(col3,LOW);
  digitalWrite(col4,LOW);

  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);

  for (int i = 0; i<5; i++) {
    digitalWrite(cols[i],HIGH);
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,colData[i]);
    digitalWrite(latchPin,HIGH);
    delay(200);

    digitalWrite(cols[i], LOW);
  }
}

void loop() {

  
  // walk through

  
//    digitalWrite(col0,LOW);
//    digitalWrite(col1,HIGH);
//    digitalWrite(latchPin,LOW);
//    digitalWrite(row0,LOW);
//    digitalWrite(row1,HIGH);
//    digitalWrite(row2,LOW);
//    shiftOut(dataPin,clockPin,LSBFIRST,colData[]);
//    digitalWrite(latchPin,HIGH);
//    delay(300);

  for (int i = 0; i<5; i++) {
    digitalWrite(cols[i],HIGH);
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,colData[i]);
    digitalWrite(latchPin,HIGH);
    delay(3);

    digitalWrite(cols[i], LOW);
  }
  

}
