
#define BASE_STEPS_PER_REV 32
#define GEAR_REDUCTION 64  // 1:64 reduction, most common
// #define GEAR_REDUCTION 16  // 1:16 reduction, less common

#define STEPS_PER_REV (BASE_STEPS_PER_REV * GEAR_REDUCTION)

#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6

#define ENABLE 8

/*
Motor Hookup
Blue - OUT1
Yellow - OUT2
Pink - OUT3
Orange - OUT4
Red - Ground
*/


// #define FWD 22
// #define REV 23
// #define SPEED_IN A0

// #define SPEED 255

#include <Stepper.h>

Stepper motor(STEPS_PER_REV, IN1, IN2, IN3, IN4);

void setup()
{
    // pinMode(FWD, INPUT_PULLUP);
    // pinMode(REV, INPUT_PULLUP);
    // pinMode(SPEED_IN, INPUT);

    pinMode(ENABLE, OUTPUT);
    digitalWrite(ENABLE, LOW);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    while (!Serial);
    Serial.begin(115200);

    motor.setSpeed(16);
}

void loop()
{
  // motor.step(STEPS_PER_REV);
  // delay(250);
  // motor.step(STEPS_PER_REV * -1);
  // delay(250);
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    // bool neg = steps < 0;
    // steps = abs(steps);

    // steps = map(steps, 0, 360, 0, STEPS_PER_REV);
    // if(neg){ steps *= -1; }
    // Serial.println(steps);
    digitalWrite(ENABLE, HIGH);
    motor.step(steps);
    digitalWrite(ENABLE, LOW);
  }
}
