#include "DriveMotor.h"

#include "Arduino.h"
#include <SoftwareSerial.h>

DriveMotor::DriveMotor(AbstractMotor* motor) {
    this->motor = motor;
    speedRamper = new SpeedRamper(0.001, 0.001);
}

DriveMotor::~DriveMotor() {
    delete motor;
    delete speedRamper;
}

void DriveMotor::setSpeed(int speed) {
    commandedSpeed = speed;
    if(speed < 0) {
        limitedSpeed = isAboveLimit(speed) ? speedLimit * -1 : speed;
    } else {
        limitedSpeed = isAboveLimit(speed) ? speedLimit : speed;
    }

    if(emergencyStopEnabled) {
        Serial.println("Emergency stop enabled. Ignoring speed change.");
    } else {
        speedRamper->setTargetSpeed(limitedSpeed);
    }
}

bool DriveMotor::isAboveLimit(int speed) {
    return abs(speed) > speedLimit;
}

void DriveMotor::setSpeedLimit(int limit) {
    speedLimit = limit;
    setSpeed(commandedSpeed);
}

void DriveMotor::setAccelerationRamping(double rate) {
    speedRamper->setAccelerationRate(rate);
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