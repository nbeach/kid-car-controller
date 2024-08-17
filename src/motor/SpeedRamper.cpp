#include "SpeedRamper.h"
#include "AbstractMotor.h"
#include <Arduino.h>

SpeedRamper::SpeedRamper(double decelerationRampingRate) { this->decelerationRampingRate = decelerationRampingRate; }

void SpeedRamper::setCurrentSpeed(int speed) {
  currentSpeed = speed;
  timeCurrentSpeedSet = millis();
}

int SpeedRamper::getCurrentSpeed() { return currentSpeed; }

void SpeedRamper::setTargetSpeed(int speed) { targetSpeed = speed; }

void SpeedRamper::tick() {
  bool isDeceleratingAcrossZero = (currentSpeed > 0 && targetSpeed <= 0) || (currentSpeed < 0 && targetSpeed >= 0);
  bool isDeceleratingOnOneSideOfZero = abs(currentSpeed) > abs(targetSpeed);
  bool isDecelerating = isDeceleratingAcrossZero || isDeceleratingOnOneSideOfZero;
  // bool isReversing = targetSpeed < 0 && currentSpeed <= 0 && currentSpeed >=
  // targetSpeed;

  double newSpeed;
  if (isDecelerating) {
    int timePassedSinceCurrentSpeedSet = millis() - timeCurrentSpeedSet;
    double timeItWouldTakeToAccelerateToCurrentSpeed = currentSpeed / decelerationRampingRate;
    ;
    int numberLineDirection = targetSpeed >= currentSpeed ? 1 : -1;
    newSpeed = decelerationRampingRate *
               (timeItWouldTakeToAccelerateToCurrentSpeed + (timePassedSinceCurrentSpeedSet * numberLineDirection));

    bool overshotTargetDeceleratingFromForward = currentSpeed > targetSpeed && newSpeed < targetSpeed;
    bool overshotTargetDeceleratingFromReverse = currentSpeed < targetSpeed && newSpeed > targetSpeed;
    if (overshotTargetDeceleratingFromForward || overshotTargetDeceleratingFromReverse)
      newSpeed = targetSpeed;
  } else {
    newSpeed = targetSpeed;
  }

  setCurrentSpeed(newSpeed);
}