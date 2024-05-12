#include "RampingMotor.h"
#include "Arduino.h"

int RampingMotor::setCurrentSpeed(int speed) {
  if(speed == currentSpeed || currentSpeed == targetSpeed) return currentSpeed;
  currentSpeed = speed;
  timeCurrentSpeedSet = millis();
  return baseMotor->setSpeed(currentSpeed);
}

void RampingMotor::stepTowardsTargetSpeed() {
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


RampingMotor::RampingMotor(AbstractMotor* baseMotor) {
  this->baseMotor = baseMotor;
}

int RampingMotor::setSpeed(int speed) {
  initialSpeed = currentSpeed;
  targetSpeed = speed;
  timeCurrentSpeedSet = millis();
  return speed;
}

void RampingMotor::setRampingRate(double rampingRate) {
  this->rampingRate = rampingRate;
  Serial.println("Ramping Rate: " + String(rampingRate));
}

void RampingMotor::tick() {
  stepTowardsTargetSpeed();
}
