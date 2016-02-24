#include <Wire.h>
#include <Servo.h>
 
#define SLAVE_ADDRESS 0x04 // Discover real

Servo servo;
byte values[2] = {0,0};
byte servoPin = 8;
byte motorPin = 11;
 
void setup() {
 servo.attach(servoPin);
 pinMode(motorPin, OUTPUT);
 
 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);
}

void loop() {}
 
// callback for received data
void receiveData(int byteCount){
 
  if (Wire.available() == 2 ) {
    values[0] = Wire.read();
    values[1] = Wire.read();

    servo.write(values[0]);
    analogWrite(motorPin, values[1]);
  }
}
 
// callback for sending data
void sendData(){
  // Kill switch interrupt stuff
  // if interrupt: Wire.write(1);
  // else: Wire.write(0);
}
