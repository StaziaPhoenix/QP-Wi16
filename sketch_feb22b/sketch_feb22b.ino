const int latchPin = 22;
const int clockPin = 23;
const int dataPin = 24;


unsigned short colData[10] = {
byte cols[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
byte rows[12] = {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};
void setup() {
  for( int i = 0; i < 10; i++) {
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], LOW);
  }
  for( int i = 0; i < 12; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], LOW);
  }

  for (int j = 0; j < 10; j++) {
    digitalWrite(cols[j], HIGH);

    
    
    delay(75);
    digitalWrite(cols[j], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
