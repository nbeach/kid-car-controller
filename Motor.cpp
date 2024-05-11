#include <SoftwareSerial.h>
#include "CytronMotorDriver.h"

class AbstractMotor {
  public:
  virtual void setSpeed(int speed);
};

class NullMotor : public AbstractMotor {
  public: 
  void setSpeed(int speed) {}
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
};

// class RealCompositeMotor : public AbstractMotor {
//   private:
//   int count;
//   AbstractMotor* motors;

//   public: 
//   RealCompositeMotor(int count, AbstractMotor* motors) {
//     this->count = count;
//     this->motors = motors;
//   }

//   void setSpeed(int speed) {
//     for (int i = 0; i < count; i++) {
//       motors[i].setSpeed(speed);
//     }
//   }
// };

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
};

class RampingMotor : public AbstractMotor {
    private:
    AbstractMotor* baseMotor;
    double stepsPerMillisecond;
    int currentSpeed = 0;
    int timeSpeedSet = 0;
    int targetSpeed = 0;

    void setCurrentSpeed(int speed) {
      if(currentSpeed == speed) return;
      currentSpeed = speed;
      timeSpeedSet = millis();
      Serial.println("Commanded Speed: " + String(speed));
      baseMotor->setSpeed(speed);
    }

    void stepTowardsTargetSpeed() {
      const double minimumDecelerationRate = 2.5;
      if(currentSpeed == targetSpeed) return;

      bool isDeceleratingFromReverse = currentSpeed < 0 && targetSpeed > currentSpeed;
      bool isDeceleratingFromForward = currentSpeed > 0 && targetSpeed < currentSpeed;
      bool isAcceleratingForward = currentSpeed >= 0 && currentSpeed < targetSpeed;
      bool isDecelerating = isDeceleratingFromForward || isDeceleratingFromReverse;

      int timePassedSinceSpeedSet = millis() - timeSpeedSet;
      double adjustedStepsPerMillisecond = isDecelerating ? minimumDecelerationRate : stepsPerMillisecond; //Limit how deceleration ramping for safety
      int speedChange = timePassedSinceSpeedSet * adjustedStepsPerMillisecond;
      
      Serial.println("Next Speed Step: " + String(speedChange));
      if(isAcceleratingForward || isDeceleratingFromReverse) {
        int newSpeed = currentSpeed + speedChange;
        setCurrentSpeed(newSpeed >= targetSpeed ? targetSpeed : newSpeed);
      } else {
         int newSpeed = currentSpeed - speedChange;
        setCurrentSpeed(newSpeed <= targetSpeed ? targetSpeed : newSpeed);
      }
    }

    public:
    RampingMotor(AbstractMotor* baseMotor) {
      this->stepsPerMillisecond = 0.5;
      this->baseMotor = baseMotor;
    }

    void setSpeed(int speed) {
      targetSpeed = speed;
      setCurrentSpeed(currentSpeed);   
    }

    void setMaxSpeedStepsPerMillisecond(double stepsPerMillisecond) {
      this->stepsPerMillisecond = stepsPerMillisecond;
      Serial.println("Ramping Rate: " + String(stepsPerMillisecond));
    }

    void tick() {
      stepTowardsTargetSpeed();
    }
};

class SpeedLimitedMotor : public AbstractMotor {
  private:
  AbstractMotor* baseMotor;
  int speedLimit = 256;

  public: 
  SpeedLimitedMotor(AbstractMotor* baseMotor) {
    this->baseMotor = baseMotor;
  }

  void setSpeed(int speed) {
    int maxForwardSpeed = speedLimit;
    int maxReverseSpeed = speedLimit * -1;

    int newSpeed = speed;
    if(speed > maxForwardSpeed) newSpeed = maxForwardSpeed;
    else if(speed < maxReverseSpeed) newSpeed = maxReverseSpeed;
  
    if(speed > maxForwardSpeed || speed < maxReverseSpeed) Serial.println("Limited Speed: " + String(newSpeed));
    baseMotor->setSpeed(newSpeed);
  }

  void setSpeedLimit(int limit) {
    speedLimit = limit;
    Serial.println("Speed Limit: " + String(limit));
  }
};

class EmergencyStopMotor : public AbstractMotor {
  private:
  AbstractMotor* baseMotor;
  bool stop = false;

  public: 
  EmergencyStopMotor(AbstractMotor* baseMotor) {
    this->baseMotor = baseMotor;
  }

  void setSpeed(int speed) {
    if(stop) Serial.println("Emergency Stop Enabled");
    baseMotor->setSpeed(stop ? 0 : speed);
  }

  void toggleEmergencyStop() {
    stop = !stop;
    if(stop) setSpeed(0);
  }
};

class RampingSpeedLimitedEmergencyStopMotor : public AbstractMotor {
  private:
  EmergencyStopMotor* emergencyStopMotor;
  SpeedLimitedMotor* speedLimitedMotor;
  RampingMotor* rampingMotor;

  public:
  RampingSpeedLimitedEmergencyStopMotor(AbstractMotor* baseMotor) {
    this->emergencyStopMotor = new EmergencyStopMotor(baseMotor);
    this->speedLimitedMotor = new SpeedLimitedMotor(this->emergencyStopMotor);
    this->rampingMotor = new RampingMotor(this->speedLimitedMotor);
  }

  void setSpeed(int speed) {
    this->rampingMotor->setSpeed(speed);
  }

  void setMaxSpeedStepsPerMillisecond(double stepsPerMillisecond) {
    this->rampingMotor->setMaxSpeedStepsPerMillisecond(stepsPerMillisecond);
  }

  void setSpeedLimit(int limit) {
    this->speedLimitedMotor->setSpeedLimit(limit);
  }

  void toggleEmergencyStop() {
    this->emergencyStopMotor->toggleEmergencyStop();
  }

  void tick() {
    this->rampingMotor->tick();
  }
};