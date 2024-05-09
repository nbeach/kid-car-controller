#include "CytronMotorDriver.h"

class AbstractDrivetrain {
  public:
  virtual void setSpeed(int speed);
};

class Drivetrain {
  protected:
  CytronMD frontLeftMotor = CytronMD(PWM_DIR, 5, 4);
  CytronMD frontRightMotor = CytronMD(PWM_DIR, 10, 12);
  CytronMD rearLeftMotor = CytronMD(PWM_DIR, 3, 2);
  CytronMD rearRightMotor = CytronMD(PWM_DIR, 6, 7);

  public: 
  void setSpeed(int speed) {
    frontLeftMotor.setSpeed(speed);
    frontRightMotor.setSpeed(speed);
    rearLeftMotor.setSpeed(speed); 
    rearRightMotor.setSpeed(speed);
  }

};

class EasingDrivetrain : AbstractDrivetrain {
    AbstractDrivetrain baseDrivetrain;

    public:
    EasingDrivetrain(AbstractDrivetrain baseDrivetrain) {
      baseDrivetrain = baseDrivetrain;
    }

    void setSpeed(int speed) {
      baseDrivetrain.setSpeed(speed);
    }
};