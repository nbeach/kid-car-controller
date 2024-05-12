#include "RampingSpeedLimitedEmergencyStopMotor.h"
#include "Arduino.h"

RampingSpeedLimitedEmergencyStopMotor::RampingSpeedLimitedEmergencyStopMotor(AbstractMotor* baseMotor) {
    this->emergencyStopMotor = new EmergencyStopMotor(baseMotor);
    this->speedLimitedMotor = new SpeedLimitedMotor(this->emergencyStopMotor);
    this->rampingMotor = new RampingMotor(this->speedLimitedMotor);
}

int RampingSpeedLimitedEmergencyStopMotor::setSpeed(int speed) {
    return this->rampingMotor->setSpeed(speed);
}

void RampingSpeedLimitedEmergencyStopMotor::setRampingRate(double rampingRate) {
    this->rampingMotor->setRampingRate(rampingRate);
}

void RampingSpeedLimitedEmergencyStopMotor::setSpeedLimit(int limit) {
    this->speedLimitedMotor->setSpeedLimit(limit);
}

void RampingSpeedLimitedEmergencyStopMotor::toggleEmergencyStop() {
    this->emergencyStopMotor->toggleEmergencyStop();
}

void RampingSpeedLimitedEmergencyStopMotor::tick() {
    this->rampingMotor->tick();
}
