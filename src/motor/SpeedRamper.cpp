#include "SpeedRamper.h"

#include "Arduino.h"
#include "AbstractMotor.h"

SpeedRamper::SpeedRamper(double accelerationRampingRate, double decelerationRampingRate) {
    this->accelerationRampingRate = accelerationRampingRate;
    this->decelerationRampingRate = decelerationRampingRate;
}

void SpeedRamper::setCurrentSpeed(int speed) {
    if(speed == currentSpeed || currentSpeed == targetSpeed) return currentSpeed;
    currentSpeed = speed;
    timeCurrentSpeedSet = millis();
}

int SpeedRamper::getCurrentSpeed() {
    return currentSpeed;
}

void SpeedRamper::setTargetSpeed(int speed) {
    initialSpeed = currentSpeed;
    targetSpeed = speed;
    timeCurrentSpeedSet = millis();
    return speed;
}

void SpeedRamper::setAccelerationRate(double rate) {
    this->accelerationRampingRate = rate;
}

void SpeedRamper::setDecelerationRate(double rate) {
    this->decelerationRampingRate = rate;
}

void SpeedRamper::tick() {
    bool isAcceleratingForward = (targetSpeed > 0) && (currentSpeed < targetSpeed);
    bool isAcceleratingBackward = (targetSpeed < 0) && (currentSpeed > targetSpeed);
    bool isDeceleratingFromReverse = (currentSpeed < 0) && (targetSpeed > currentSpeed);
    bool isDeceleratingFromForward = (currentSpeed > 0) && (targetSpeed < currentSpeed);
    bool isAccelerating = isAcceleratingForward || isAcceleratingBackward;
    bool isDecelerating = isDeceleratingFromForward || isDeceleratingFromReverse;

    int timePassedSinceCurrentSpeedSet = millis() - timeCurrentSpeedSet;
    double rampingRateForDirection = isDecelerating ? decelerationRampingRate : accelerationRampingRate;
    double timeItWouldTakeToAccelerateToCurrentSpeed = sqrt((1 / rampingRateForDirection) * abs(currentSpeed));
    int changeDirection = isDecelerating ? -1 : 1;
    double speedChangeFromInitial = rampingRateForDirection * pow(timeItWouldTakeToAccelerateToCurrentSpeed + (timePassedSinceCurrentSpeedSet * changeDirection), 2);
    speedChangeFromInitial =  (isAcceleratingBackward || isDeceleratingFromReverse) ? speedChangeFromInitial * -1 : speedChangeFromInitial;

    int newSpeed;
    if(isAcceleratingForward || isDeceleratingFromReverse) {
        newSpeed = speedChangeFromInitial >= targetSpeed ? targetSpeed : speedChangeFromInitial;
    } else {
        newSpeed = speedChangeFromInitial <= targetSpeed ? targetSpeed : speedChangeFromInitial;
    }

    setCurrentSpeed(newSpeed);
}