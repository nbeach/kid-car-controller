#include "DriveMotor.h"

#include "Arduino.h"
#include <SoftwareSerial.h>

DriveMotor::DriveMotor(AbstractMotor* motor) {
    this->motor = motor;
    speedRamper = new SpeedRamper(0.088);
}

DriveMotor::~DriveMotor() {
    delete motor;
    delete speedRamper;
}

void DriveMotor::setSpeed(int speed) {
    commandedSpeed = speed;

    double throttlePercentage = speed / 256.0;
    int newSpeed = throttlePercentage * speedLimit;

    if(emergencyStopEnabled) {
        Serial.println("Emergency stop enabled. Ignoring speed change.");
    } else {
        speedRamper->setTargetSpeed(newSpeed);
    }
}

bool DriveMotor::isAboveLimit(int speed) {
    return abs(speed) > speedLimit;
}

void DriveMotor::setSpeedLimit(int limit) {
    speedLimit = limit;
    setSpeed(commandedSpeed);
}

void DriveMotor::tick() {
    int priorSpeed = speedRamper->getCurrentSpeed();
    speedRamper->tick();
    int speed = speedRamper->getCurrentSpeed();

    if(emergencyStopEnabled) {
        speedRamper->setTargetSpeed(0);
        speedRamper->setCurrentSpeed(0);
        motor->setSpeed(0);
    } else if(speed != priorSpeed)  {
        motor->setSpeed(speed);
    }

}

bool DriveMotor::toggleEmergencyStop() {
    emergencyStopEnabled = !emergencyStopEnabled;
    if(emergencyStopEnabled) {
        speedRamper->setTargetSpeed(0);
        speedRamper->setCurrentSpeed(0);
        motor->setSpeed(0);
    } else {
        setSpeed(commandedSpeed);
    }
    return emergencyStopEnabled;
}