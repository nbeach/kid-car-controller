#include <SoftwareSerial.h>
#include "CytronMotorDriver.h"

class AbstractMotor {
  public:
  virtual int setSpeed(int speed);
};

class NullMotor : public AbstractMotor {
  public: 
  int setSpeed(int speed) { return speed; }
};

class Motor : public AbstractMotor {
  private:
  CytronMD* motor;

  public: 
  Motor(int pin1, int pin2) {
    motor = new CytronMD(PWM_DIR, pin1, pin2);
  }

  int setSpeed(int speed) {
    motor->setSpeed(speed);
    return speed;
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
  int setSpeed(int speed) {
    frontLeftMotor.setSpeed(speed);
    frontRightMotor.setSpeed(speed);
    rearLeftMotor.setSpeed(speed); 
    rearRightMotor.setSpeed(speed);
    return speed;
  }
};

class RampingMotor : public AbstractMotor {
    private:
    AbstractMotor* baseMotor;

    double rampingRate = 0.001;
    double decelerationRampingRate = 0.001;
    int initialSpeed = 0;
    int currentSpeed = 0;
    int targetSpeed = 0;
    int timeCurrentSpeedSet = 0;

    int setCurrentSpeed(int speed) {
      if(speed == currentSpeed || currentSpeed == targetSpeed) return currentSpeed;
      currentSpeed = speed;
      timeCurrentSpeedSet = millis();
      Serial.println("Commanded Speed: " + String(speed));
      return baseMotor->setSpeed(currentSpeed);
    }

    void stepTowardsTargetSpeed() {
      if(currentSpeed == targetSpeed) return;
      bool isAcceleratingForward = (targetSpeed > 0) && (currentSpeed < targetSpeed);
      bool isAcceleratingBackward = (targetSpeed < 0) && (currentSpeed > targetSpeed);
      bool isDeceleratingFromReverse = (currentSpeed < 0) && (targetSpeed > currentSpeed);
      bool isDeceleratingFromForward = (currentSpeed > 0) && (targetSpeed < currentSpeed);
      bool isAccelerating = isAcceleratingForward || isAcceleratingBackward;
      bool isDecelerating = isDeceleratingFromForward || isDeceleratingFromReverse;

      int timePassedSinceCurrentSpeedSet = millis() - timeCurrentSpeedSet;
      double rampingRateForDirection = isDecelerating ? decelerationRampingRate : rampingRate;
      double timeItWouldTakeToAccelerateToCurrentSpeed = sqrt((1 / rampingRateForDirection) * abs(currentSpeed));
      int changeDirection = isDecelerating ? -1 : 1;
      double speedChangeFromInitial = rampingRateForDirection * pow(timeItWouldTakeToAccelerateToCurrentSpeed + (timePassedSinceCurrentSpeedSet * changeDirection), 2);
      speedChangeFromInitial =  (isAcceleratingBackward || isDeceleratingFromReverse) ? speedChangeFromInitial * -1 : speedChangeFromInitial;

      if(isAcceleratingForward || isDeceleratingFromReverse) {
          int newSpeed = speedChangeFromInitial >= targetSpeed ? targetSpeed : speedChangeFromInitial;
          int actual = setCurrentSpeed(newSpeed);
          if(actual != newSpeed) setSpeed(actual);
      } else {
          int newSpeed = speedChangeFromInitial <= targetSpeed ? targetSpeed : speedChangeFromInitial;
          int actual = setCurrentSpeed(newSpeed);
          if(actual != newSpeed) setSpeed(actual);
      }
    }

    public:
    RampingMotor(AbstractMotor* baseMotor) {
      this->baseMotor = baseMotor;
    }

    int setSpeed(int speed) {
      initialSpeed = currentSpeed;
      targetSpeed = speed;
      timeCurrentSpeedSet = millis();
      return speed;
    }

    void setRampingRate(double rampingRate) {
      this->rampingRate = rampingRate;
      Serial.println("Ramping Rate: " + String(rampingRate));
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

  int setSpeed(int speed) {
    int maxForwardSpeed = speedLimit;
    int maxReverseSpeed = speedLimit * -1;

    int newSpeed = speed;
    if(speed > maxForwardSpeed) newSpeed = maxForwardSpeed;
    else if(speed < maxReverseSpeed) newSpeed = maxReverseSpeed;
  
    if(speed > maxForwardSpeed || speed < maxReverseSpeed) Serial.println("Limited Speed: " + String(newSpeed));
    return baseMotor->setSpeed(newSpeed);
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

  int setSpeed(int speed) {
    if(speed != 0 && stop) Serial.println("Speed Change Ignored. Emergency Stop Enabled.");
    return baseMotor->setSpeed(stop ? 0 : speed);
  }

  void toggleEmergencyStop() {
    stop = !stop;
    Serial.println("Emergency Stop Enabled: " + String(stop));
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

  int setSpeed(int speed) {
    return this->rampingMotor->setSpeed(speed);
  }

  void setRampingRate(double rampingRate) {
    this->rampingMotor->setRampingRate(rampingRate);
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