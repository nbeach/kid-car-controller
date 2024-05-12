#include "EmergencyStopMotor.h"
#include <SoftwareSerial.h>

EmergencyStopMotor::EmergencyStopMotor(AbstractMotor* baseMotor) {
    this->baseMotor = baseMotor;
}

int EmergencyStopMotor::setSpeed(int speed) {
    if(speed != 0 && stop) Serial.println("Speed Change Ignored. Emergency Stop Enabled.");
    return baseMotor->setSpeed(stop ? 0 : speed);
}

void EmergencyStopMotor::toggleEmergencyStop() {
    stop = !stop;
    Serial.println("Emergency Stop Enabled: " + String(stop));
    if(stop) setSpeed(0);
}

