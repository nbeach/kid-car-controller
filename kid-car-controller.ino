#include <SoftwareSerial.h>
#include "CytronMotorDriver.h"
#include "Cytron_PS2Shield.h"
#include "Controller.cpp"

// Cytron_PS2Shield ps2(8,9);
Controller controller;
CytronMD frontLeftMotor(PWM_DIR, 5, 4);
CytronMD frontRightMotor(PWM_DIR, 10, 12);
CytronMD rearLeftMotor(PWM_DIR, 3, 2);
CytronMD rearRightMotor(PWM_DIR, 6, 7);

void setup()
{
  controller = Controller();
  // ps2.begin(9600);
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  int throttle = controller.throttle();
  Serial.println(throttle);
  frontLeftMotor.setSpeed(throttle);
  frontRightMotor.setSpeed(throttle);
  rearLeftMotor.setSpeed(throttle);
  rearRightMotor.setSpeed(throttle);
  delay(100);
}


