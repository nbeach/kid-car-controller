#include "EmergencyStopMotor.h"
#include <SoftwareSerial.h>

EmergencyStopMotor::EmergencyStopMotor(AbstractMotor* baseMotor) {
    this->baseMotor = baseMotor;
}

int EmergencyStopMotor::setSpeed(int speed) {
    lastCommandedSpeed = speed;
    if(speed != 0 && stop) Serial.println("Speed Change Ignored. Emergency Stop Enabled.");
    return baseMotor->setSpeed(stop ? 0 : speed);
}

bool EmergencyStopMotor::toggleEmergencyStop() {
    if(stop && lastCommandedSpeed != 0) {
        Serial.println("Commanded speed not zero. Ignoring request to disable emergency stop.");
        return stop;
    }
    stop = !stop;
    if(stop) baseMotor->setSpeed(0);
    return stop;
}

