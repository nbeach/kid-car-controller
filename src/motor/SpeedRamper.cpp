#include "SpeedRamper.h"
#include "AbstractMotor.h"

SpeedRamper::SpeedRamper(double decelerationRampingRate) {
  this->decelerationRampingRate = decelerationRampingRate;
}

void SpeedRamper::setCurrentSpeed(int speed) {
  currentSpeed = speed;
  timeCurrentSpeedSet = millis();
}

int SpeedRamper::getCurrentSpeed() { return currentSpeed; }

void SpeedRamper::setTargetSpeed(int speed) { targetSpeed = speed; }

void SpeedRamper::tick() {
  bool isDeceleratingAcrossZero = (currentSpeed > 0 && targetSpeed <= 0) ||
                                  (currentSpeed < 0 && targetSpeed >= 0);
  bool isDeceleratingOnOneSideOfZero = abs(currentSpeed) > abs(targetSpeed);
  bool isDecelerating =
      isDeceleratingAcrossZero || isDeceleratingOnOneSideOfZero;
  // bool isReversing = targetSpeed < 0 && currentSpeed <= 0 && currentSpeed >=
  // targetSpeed;

  double newSpeed;
  if (isDecelerating) {
    int timePassedSinceCurrentSpeedSet = millis() - timeCurrentSpeedSet;
    double timeItWouldTakeToAccelerateToCurrentSpeed =
        currentSpeed / decelerationRampingRate;
    ;
    int numberLineDirection = targetSpeed >= currentSpeed ? 1 : -1;
    newSpeed = decelerationRampingRate *
               (timeItWouldTakeToAccelerateToCurrentSpeed +
                (timePassedSinceCurrentSpeedSet * numberLineDirection));
    if (targetSpeed == 0 && currentSpeed < 0 && newSpeed > 0)
      newSpeed = 0;
    if (targetSpeed == 0 && currentSpeed > 0 && newSpeed < 0)
      newSpeed = 0;
  } else {
    newSpeed = targetSpeed;
  }

  setCurrentSpeed(newSpeed);
}