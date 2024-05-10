#include "CytronMotorDriver.h"

class AbstractMotor {
  public:
  virtual void setSpeed(int speed);
  virtual void tick();
};

class CompositeMotor : public AbstractMotor {
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

  void tick() {}

};

class RampingMotor : public AbstractMotor {
    protected:
    AbstractMotor* baseMotor;
    int maxStepPerTenthSecond = 13;
    int currentSpeed = 0;
    int currentSpeedSetTime = 0;
    int targetSpeed = 0;

    void setCurrentSpeed(int speed) {
      currentSpeed = speed;
      currentSpeedSetTime = millis();
      baseMotor->setSpeed(speed);
    }

    void stepTowardsTargetSpeed() {
      int minSpeedStep = currentSpeed - maxStepPerTenthSecond;
      int maxSpeedStep = currentSpeed + maxStepPerTenthSecond;

      if(targetSpeed <= maxSpeedStep && targetSpeed >= minSpeedStep) {
        setCurrentSpeed(targetSpeed);
      } else {
        setCurrentSpeed(currentSpeed + maxStepPerTenthSecond);
      }
    }

    int timeSinceCurrentSpeedSetMilliSeconds() {
      int currentTime = millis();
      return currentTime - currentSpeedSetTime;
    }


    public:
    RampingMotor(AbstractMotor* baseMotor) {
      this->baseMotor = baseMotor;
    }

    void setSpeed(int speed) {
      targetSpeed = speed;
      stepTowardsTargetSpeed();
    }

    void tick() {
      if(currentSpeed == targetSpeed) return;
      int currentTime = millis();

      if(timeSinceCurrentSpeedSetMilliSeconds() >= 100) {
        stepTowardsTargetSpeed();
      }
    }
};