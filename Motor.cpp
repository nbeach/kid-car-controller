#include <SoftwareSerial.h>
#include "CytronMotorDriver.h"

class AbstractMotor {
  public:
  virtual void setSpeed(int speed);
  virtual void tick();
};

class Motor : public AbstractMotor {
  private:
  CytronMD* motor;

  public: 
  Motor(int pin1, int pin2) {
    motor = new CytronMD(PWM_DIR, pin1, pin2);
  }

  void setSpeed(int speed) {
    motor->setSpeed(speed);
  }

  void tick() {}
};



class RealCompositeMotor : public AbstractMotor {
  private:
  int count;
  AbstractMotor* motors;

  public: 
  RealCompositeMotor(int count, AbstractMotor* motors) {
    this->count = count;
    // this.motors = motors;
  }

  void setSpeed(int speed) {
    for (int i = 0; i < count; i++) {
      motors[i].setSpeed(speed);
    }
  }

  void tick() {
     for (int i = 0; i < count; i++) {
      motors[i].tick();
    }
  }
};

class CompositeMotor : public AbstractMotor {
  private:
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
    private:
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

    void setStepsPerMillisecond(double stepsPerMillisecond) {
      this->stepsPerMillisecond = stepsPerMillisecond;
    }

    void tick() {
      stepTowardsTargetSpeed();
    }
};