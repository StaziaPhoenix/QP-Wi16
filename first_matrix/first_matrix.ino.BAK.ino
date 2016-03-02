#include <DHT.h>
#include <idDHT11.h>

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 13;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 11;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 9;

byte col0 = 2;
byte col1 = 3;
byte col2 = 4;
byte col3 = 5;
byte col4 = 6;
//global var, number of columns in the grid 
int numCol= 5;
int numRow = 5;



int bright = 0;
int fade = 200;
int shock = 7; 
int val;

int modeFlag = 0;
int joyX = A5;
int joyY = A4; 

int togglePwr = 8;
int prevToggle; 

//byte row0 = 22;
//byte row1 = 25;
//byte row2 = 26;

byte colDataInit[5] = {0xFf, 0xFf, 0xff, 0xFf, 0xFf};
byte colData[5] = {0, 0, 0, 0, 0};
byte cols[5] = {col0, col1, col2, col3, col4};



void setup() {
  Serial.begin(9600);
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
  
  pinMode(togglePwr, INPUT);
  pinMode(shock, INPUT); 

  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);

  for (int i = 0; i<5; i++) {
    digitalWrite(cols[i],HIGH);
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,colDataInit[i]);
    digitalWrite(latchPin,HIGH);
    delay(200);

    digitalWrite(cols[i], LOW);
  }

   Serial.print("joyX analog :");
  Serial.print(analogRead(joyX));
  Serial.print("\n");
  Serial.print("joyY analog :");
  Serial.print(analogRead(joyY));
  Serial.print("\n");
}


void loop() { 
  //Serial.print(digitalRead(shock));
  // If conditions for checking sensor states
  if (digitalRead(shock) == LOW) 
  {
    //delay the frequency at which the 
    delay(50);
  }
  // control matrix based on sensors
  setData();
  defDisplay(); 
  
}

//default display 
void defDisplay()
{
  // control matrix based on sensors
  setData();
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 5; i++) {
       vibration();

      if (digitalRead(togglePwr) == LOW) 
      {
        modeFlag = modeFlag^1;
        setData();
        j = 0;
        i = 0;
      }
      joyStk(i);
      digitalWrite(cols[i],HIGH);    
      
      digitalWrite(cols[i],HIGH);
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
      digitalWrite(latchPin,HIGH);
      delay(100);
  
      digitalWrite(cols[i], LOW);
      //adjustData(i);
    }
  }
}
void vibration() {
    for (int i =0; i < 5; i++)
    {
      digitalWrite(cols[i], HIGH);
      delay(40);
    }
    for (int i =0; i <5; i++)
    {
      digitalWrite(cols[i], LOW); 
      delay(40);
    }
    delay(100);
  }

      adjustData(i);
    }
  }

  /*
  val  = digitalRead(shock); 
   if (val == HIGH)
  {
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(cols[i], HIGH);
    }
  }
  else 
  {
     for (int i = 0; i < 5; i++)
     {
        digitalWrite(cols[i], LOW); 
     }
  }
 */

 //joyStk();
 /*
 Serial.print("joyX analog :");
  Serial.print(analogRead(joyX));
  Serial.print("\n");
  Serial.print("joyY analog :");
  Serial.print(analogRead(joyY));
  Serial.print("\n");
  delay(500); 
  */
  /*
  setData();
>>>>>>> 03be70a57d0e9e49151cd7c03d09af6fc52ac4af

void pattern1() 
{
  int mid = numCol%2;
  digitalWrite(cols[mid], HIGH);
  delay(30);
   
}

void joyStk(int i) 
{
  
  int set = i;
  if (analogRead(joyY) >= 800) {
    for(int j = 0; i < numCol; j++) {
//      byte temp = colData[j] & 0x01;
//      temp = temp >> (numRow-1);
      colData[i] = (colData[i] >> 1); // | temp;
    }
  }
  if (analogRead(joyY) <= 300) {
    for(int j = 0; i < numCol; j++) {
//      byte temp = colData[j] & 0x08;
//      temp = temp << (numRow-1);
      colData[i] = (colData[i] << 1); // | temp;
    }
  }
  if (analogRead(joyX) >= 800) {
    byte temp = colData[numCol-1];
    for (int j = 0; j < numCol; j++) {
      colData[j] = colData[j+1];
    }
    colData[0] = temp;
  }
  if(analogRead(joyX) <= 300) {
    byte temp = colData[0];
    for(int j = 0; j < numCol; j++) {
      colData[j] = colData[j-1];
    }
    colData[numCol-1];
  }
  */
  //temp();
  //toggle();
}
void clearGrid() {
  for(int i = 0; i < 5; i++) 
  {
    cols[i] = 0;
  }
}

void vibration() {
  Serial.print(digitalRead(shock));
  if (digitalRead(shock) == HIGH)
  {
    for (int i =0; i < 5; i++)
    {
      digitalWrite(cols[i], LOW);
      delay(40);
    }
  }
  else 
  {
    for (int i = 0; i < 5; i++) 
    {
      digitalWrite(cols[i], HIGH);
    }
  }
}

void joyStk() 
{
  Serial.print("joyX analog :");
  Serial.print(analogRead(joyX));
  Serial.print("\n");
  Serial.print("joyY analog :");
  Serial.print(analogRead(joyY));
  Serial.print("\n"); 
  delay(500); 
}

void setData() {
  //colData[1] = 0x30;

  for (int i = 0; i < 5; i++) {
    if (!modeFlag) {
      colData[i] = 0x01;
     }
    else 
    {
      colData[i] = colDataInit[i]; 
     }
  }
}
void adjustData(int i) {
  if (!modeFlag) {
     colData[i] = colData[i] << 1;
  }
}
void pattern1() 
{
  
<<<<<<< HEAD
//  if (set == 0) 
//  {
//    set  = numCol -1;
//  }
//  if (analogRead(joyX) <= 1023 && analogRead(joyX) > 535) 
//  {
//    cols[set] = cols[set-1];
//  }
//  if (analogRead(joyX) < 525) 
//  {
//    cols[set] = cols[set+1];
//  }
//  if (analogRead(joyY) <= 1023 && analogRead(joyY) > ) 
//  {
//    colData[set] = colData[set] >> 1; 
//  }
//  if (analogRead(joyY) <= 0) 
//  {
//    colData[set] = colData[set] << 1; 
//  }
}

void setData() {
  for (int i = 0; i < 5; i++) {
    if (!modeFlag) {
      colData[i] = 0x01;
     }
    else 
    {
//      colData[i] = colDataInit[i]; 
        colData[i] = 0x00;
     }
  }
  colData[0] = 0x01;
}
void adjustData(int i) {
  if (!modeFlag) {
     colData[i] = colData[i] << 1;
  }
}



void toggle() 
{
  
//  if (digitalRead(togglePwr) == LOW) 
//  {
//    modeFlag = modeFlag^1;
//  }
  
}


