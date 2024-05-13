#include "SpeedLimitedMotor.h"
#include <SoftwareSerial.h>

SpeedLimitedMotor::SpeedLimitedMotor(AbstractMotor* baseMotor) {
    this->baseMotor = baseMotor;
}

void SpeedLimitedMotor::setSpeed(int speed) {
    int maxForwardSpeed = speedLimit;
    int maxReverseSpeed = speedLimit * -1;

    int newSpeed = speed;
    if(speed > maxForwardSpeed) newSpeed = maxForwardSpeed;
    else if(speed < maxReverseSpeed) newSpeed = maxReverseSpeed;

    if(speed > maxForwardSpeed || speed < maxReverseSpeed) Serial.println("Limited Speed: " + String(newSpeed));
    baseMotor->setSpeed(newSpeed);
}

void SpeedLimitedMotor::setSpeedLimit(int limit) {
    speedLimit = limit;
}
