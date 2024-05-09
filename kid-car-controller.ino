#include <SoftwareSerial.h>
#include "CytronMotorDriver.h"
#include "Cytron_PS2Shield.h"

Cytron_PS2Shield ps2(8,9);
CytronMD frontLeftMotor(PWM_DIR, 5, 4);
CytronMD frontRightMotor(PWM_DIR, 10, 12);
CytronMD rearLeftMotor(PWM_DIR, 3, 2);
CytronMD rearRightMotor(PWM_DIR, 6, 7);

void setup()
{
  ps2.begin(9600);
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  int input = ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);
  int speed =  ((input-128) * -2);
  Serial.println(speed);
  frontLeftMotor.setSpeed(speed);
  frontRightMotor.setSpeed(speed);
  rearLeftMotor.setSpeed(speed);
  rearRightMotor.setSpeed(speed);
  delay(100);
}


