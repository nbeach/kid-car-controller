#include <SoftwareSerial.h>
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
    double stepsPerMillisecond;
    int currentSpeed = 0;
    int timeSpeedSet = 0;
    int targetSpeed = 0;

    void setCurrentSpeed(int speed) {
      currentSpeed = speed;
      timeSpeedSet = millis();
      baseMotor->setSpeed(speed);
      Serial.println("Motor Speed: " + String(speed));
    }

    void stepTowardsTargetSpeed() {
      if(currentSpeed == targetSpeed) return;
      int timePassedSinceSpeedSet = millis() - timeSpeedSet;
      int speedIncrease = timePassedSinceSpeedSet * stepsPerMillisecond;
      int newSpeed = currentSpeed + speedIncrease;
      currentSpeed = newSpeed >= targetSpeed ? targetSpeed : newSpeed;
    }

    public:
    RampingMotor(double stepsPerMillisecond, AbstractMotor* baseMotor) {
      this->stepsPerMillisecond = stepsPerMillisecond;
      this->baseMotor = baseMotor;
    }

    void setSpeed(int speed) {
      targetSpeed = speed;
      setCurrentSpeed(currentSpeed);
      Serial.println("Target Motor Speed: " + String(targetSpeed));

      stepTowardsTargetSpeed();
    }

    void tick() {
      stepTowardsTargetSpeed();
    }
};