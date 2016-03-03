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

int bright = 0;
int fade = 200;
int shock = 7; 
int val;

int modeFlag = 0;
int joyX = A3;
int joyY = A4; 

int togglePwr = 8;
int prevToggle; 

//byte row0 = 22;
//byte row1 = 25;
//byte row2 = 26;

byte colDataInit[5] = {0xFf, 0xFf, 0xff, 0xFf, 0xFf};
byte colData[5] = {0, 0, 0, 0, 0};
byte cols[5] = {col0, col1, col2, col3, col4};

//temp sens
//void dht11_wrapper(); 
//idDHT11 DHT11(DHT11pin , DHT11int, dht11_wrapper); 

void setup() {
  Serial.begin(9600);
  //Serial.begin(115200);
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
}
/*
void dht11_wrapper()
{
  DHT11.isrCallback();
}
*/

void loop() { 

  // If conditions for checking sensor states


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
      
      digitalWrite(cols[i],HIGH);
      
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colData[i]);
      digitalWrite(latchPin,HIGH);
      delay(100);
  
      digitalWrite(cols[i], LOW);
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

  for (int i = 0; i<5; i++) {
    digitalWrite(cols[i],HIGH);
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,colData[i]);
    digitalWrite(latchPin,HIGH);
    delay(3);

    digitalWrite(cols[i], LOW);
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
  
}
/*
void temp()
{
  DHT11.acquire();
  while(DHT11.acquiring())
  ;
  int result = DHT11.getStatus(); 
  switch (result)
  {
  case IDDHTLIB_OK: 
    Serial.println("OK"); 
    break;
  case IDDHTLIB_ERROR_CHECKSUM: 
    Serial.println("Error\n\r\tChecksum error"); 
    break;
  case IDDHTLIB_ERROR_ISR_TIMEOUT: 
    Serial.println("Error\n\r\tISR Time out error"); 
    break;
  case IDDHTLIB_ERROR_RESPONSE_TIMEOUT: 
    Serial.println("Error\n\r\tResponse time out error"); 
    break;
  case IDDHTLIB_ERROR_DATA_TIMEOUT: 
    Serial.println("Error\n\r\tData time out error"); 
    break;
  case IDDHTLIB_ERROR_ACQUIRING: 
    Serial.println("Error\n\r\tAcquiring"); 
    break;
  case IDDHTLIB_ERROR_DELTA: 
    Serial.println("Error\n\r\tDelta time to small"); 
    break;
  case IDDHTLIB_ERROR_NOTSTARTED: 
    Serial.println("Error\n\r\tNot started"); 
    break;
  default: 
    Serial.println("Unknown error"); 
    break;
  }

   Serial.print("Temperature (oC): ");
  Serial.println(DHT11.getCelsius(), 2);

  Serial.print("Temperature (oF): ");
  Serial.println(DHT11.getFahrenheit(), 2);
}
*/

void toggle() 
{
  
//  if (digitalRead(togglePwr) == LOW) 
//  {
//    modeFlag = modeFlag^1;
//  }
  
}

