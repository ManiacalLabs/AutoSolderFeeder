/* 
[Dan] - Modified version of the Adafruit Motor Shield v2 DCMotorTest example

This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

const int fwdBtnPin = 3;
const int revBtnPin = 4;
const int speedCtrlPin = A0;

int feedSpeed = 0;

void setup() {
  Serial.begin(9600);

  AFMS.begin();  // create with the default frequency 1.6KHz

  myMotor->run(RELEASE);

  pinMode(fwdBtnPin, INPUT_PULLUP);
  pinMode(revBtnPin, INPUT_PULLUP);
  
}

void loop() {
  uint8_t i;

  feedSpeed = analogRead(speedCtrlPin);
  feedSpeed = map(feedSpeed, 0, 1023, 0, 255);
  Serial.println(feedSpeed, DEC);
  
  if(!digitalRead(fwdBtnPin) && digitalRead(revBtnPin)){
    myMotor->run(FORWARD);
    myMotor->setSpeed(feedSpeed);
  }
 
  if(!digitalRead(revBtnPin) && digitalRead(fwdBtnPin)){
    myMotor->run(BACKWARD);
    myMotor->setSpeed(feedSpeed);
  }

  if(digitalRead(fwdBtnPin) && digitalRead(revBtnPin)){
    myMotor->run(RELEASE);
  }

}
