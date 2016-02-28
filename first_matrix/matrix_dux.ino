//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 13;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 11;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 9;

//columns of the led grid 
byte col0 = 2;
byte col1 = 3;
byte col2 = 4;
byte col3 = 5;
byte col4 = 6;

int numCol = 5; 
int numRow = 5;

//brightness setting 
int bright = 0;
//fade setting 
int fade = 200;
int shock = 7; 
int val;

//flag for the button key switch 
int modeFlag = 0;

//joystick x and y axis
int joyX = A3;
int joyY = A4; 

void setup() {
  Serial.begin(9600);
  //Serial.begin(115200);

  //led grid columns 
  pinMode(col0,OUTPUT);
  pinMode(col1,OUTPUT);
  pinMode(col2,OUTPUT);
  pinMode(col3,OUTPUT);
  pinMode(col4,OUTPUT);

//initialize grid off 
  digitalWrite(col0,LOW);
  digitalWrite(col1,LOW);
  digitalWrite(col2,LOW);
  digitalWrite(col3,LOW);
  digitalWrite(col4,LOW);

  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);

  //vibration sensor 
  pinMode(shock, INPUT); 

  //
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
}

//turns off the grid 
void clearGrid() {
  for(int i = 0; i < 5; i++) 
  {
    cols[i] = 0;
  }
}

//reads input from vibration sensor
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
  for (int i = 0; i < numCol; i++)
  {
    
  }
}

