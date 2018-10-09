#include "AccelStepper.h"

// Motor pin definitions
#define m1  1     // IN1 on the ULN2003 driver 1
#define m2  2     // IN2 on the ULN2003 driver 1
#define m3  3     // IN3 on the ULN2003 driver 1
#define m4  4     // IN4 on the ULN2003 driver 1

#define FWD 7
#define REV 8
#define SPEED_IN A0
#define STATUS 6

#define STEPS_FWD 4096
#define STEPS_REV -4096

#define MAX_SPEED 4000
#define MIN_SPEED 500
#define ACCEL     2000

// Initialize with pin sequence IN1-IN3-IN2-IN4 for
// using the AccelStepper with 28BYJ-48
AccelStepper motor(AccelStepper::HALF4WIRE , m1, m3, m2, m4);

void startup() {
  motor.enableOutputs();
  motor.move(STEPS_FWD);
  motor.runToPosition();
  motor.move(STEPS_REV);
  motor.runToPosition();
}

void setup() {
  pinMode(FWD, INPUT_PULLUP);
  pinMode(REV, INPUT_PULLUP);
  pinMode(SPEED_IN, INPUT);
  pinMode(STATUS, OUTPUT);

  motor.disableOutputs();
  motor.setMaxSpeed(MAX_SPEED);
  motor.setAcceleration(ACCEL);

  startup();
}



int _speed = 0;

void loop() {
  if(!digitalRead(FWD)){
    motor.enableOutputs();
    motor.move(STEPS_FWD);
    digitalWrite(STATUS, HIGH);
    motor.run();
  }
  else if(!digitalRead(REV)){
    motor.enableOutputs();
    motor.move(STEPS_REV);
    digitalWrite(STATUS, HIGH);
    motor.run();
  }
  else {
    digitalWrite(STATUS, LOW);
    motor.setCurrentPosition(0);
    motor.disableOutputs();
    _speed = analogRead(SPEED_IN);
    motor.setMaxSpeed(map(_speed, 0, 1023, MIN_SPEED, MAX_SPEED));
  }
}