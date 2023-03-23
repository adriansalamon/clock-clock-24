/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include "clock_accel_stepper.h"
#include <ShiftRegister74HC595.h>

ShiftRegister74HC595<1> sr(10, 1, 0);

const int STEPS = 360 * 12;
const int RESET = 13;


const int A1_STEP = 2;
const int B1_STEP = 3;
const int A1_DIR = 0;
const int B1_DIR = 1;

ClockAccelStepper stepper1(AccelStepper::DRIVER, A1_STEP, A1_DIR, &sr);
ClockAccelStepper stepper2(AccelStepper::DRIVER, B1_STEP, B1_DIR, &sr);


const int A2_STEP = 4;
const int B2_STEP = 5;
const int A2_DIR = 2;
const int B2_DIR = 3;

ClockAccelStepper stepper3(AccelStepper::DRIVER, A2_STEP, A2_DIR, &sr);
ClockAccelStepper stepper4(AccelStepper::DRIVER, B2_STEP, B2_DIR, &sr);


const int A3_STEP = 6;
const int B3_STEP = 7;
const int A3_DIR = 4;
const int B3_DIR = 5;

ClockAccelStepper stepper5(AccelStepper::DRIVER, A3_STEP, A3_DIR, &sr);
ClockAccelStepper stepper6(AccelStepper::DRIVER, B3_STEP, B3_DIR, &sr);

const int A4_STEP = 8;
const int B4_STEP = 9;
const int A4_DIR = 6;
const int B4_DIR = 7;

ClockAccelStepper stepper7(AccelStepper::DRIVER, A4_STEP, A4_DIR, &sr);
ClockAccelStepper stepper8(AccelStepper::DRIVER, B4_STEP, B4_DIR, &sr);

void setup()
{
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);

  const double speed = 4000.0;
  const int acc = 1000.0;

 
  stepper1.setMaxSpeed(1800.0);
  stepper1.setAcceleration(acc);
  stepper1.moveTo(180*12);
  
  stepper2.setMaxSpeed(speed);
  stepper2.setAcceleration(acc);
  stepper2.moveTo(1000000);
  
  stepper3.setMaxSpeed(speed);
  stepper3.setAcceleration(acc);
  stepper3.moveTo(1000000); 

  stepper4.setMaxSpeed(speed);
  stepper4.setAcceleration(acc);
  stepper4.moveTo(180*12);

  stepper5.setMaxSpeed(speed);
  stepper5.setAcceleration(acc);
  stepper5.moveTo(1000000);

  stepper6.setMaxSpeed(speed);
  stepper6.setAcceleration(acc);
  stepper6.moveTo(180*12);

  stepper7.setMaxSpeed(speed);
  stepper7.setAcceleration(acc);
  stepper7.moveTo(1000000);

  stepper8.setMaxSpeed(speed);
  stepper8.setAcceleration(acc);
  stepper8.moveTo(180*12);

}

int i = 0;
int steps = 0;
void loop()
{
    // Change direction at the limits
    if (stepper1.distanceToGo() == 0)
        stepper1.moveTo(-stepper1.currentPosition());

    if (stepper4.distanceToGo() == 0)
        stepper4.moveTo(-stepper4.currentPosition());

    if (stepper6.distanceToGo() == 0)
        stepper6.moveTo(-stepper6.currentPosition());

    if (stepper8.distanceToGo() == 0)
        stepper8.moveTo(-stepper8.currentPosition());

    stepper1.run();
    stepper2.run();
    stepper3.run();
    stepper4.run();
    stepper5.run();
    stepper6.run();
    stepper7.run();
    stepper8.run();

  
}
