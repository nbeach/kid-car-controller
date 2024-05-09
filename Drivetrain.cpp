#include "CytronMotorDriver.h"

class Drivetrain {
  CytronMD* frontLeftMotor;
  CytronMD* frontRightMotor;
  CytronMD* rearLeftMotor;
  CytronMD* rearRightMotor;

  public: 
  Drivetrain() {
    CytronMD frontLeftMotor = CytronMD(PWM_DIR, 5, 4);
    CytronMD frontRightMotor = CytronMD(PWM_DIR, 10, 12);
    CytronMD rearLeftMotor = CytronMD(PWM_DIR, 3, 2);
    CytronMD rearRightMotor = CytronMD(PWM_DIR, 6, 7);
  }

  void setSpeed(int speed) {
    frontLeftMotor->setSpeed(speed);
    frontRightMotor->setSpeed(speed);
    rearLeftMotor->setSpeed(speed); 
    rearRightMotor->setSpeed(speed);
  }

};
