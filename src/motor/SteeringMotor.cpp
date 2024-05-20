#include "SteeringMotor.h"

#include "AbstractMotor.h"
#include <SoftwareSerial.h>

SteeringMotor::SteeringMotor(AbstractMotor* motor, int relayPin) {
    this->motor = motor;
    this->motorRelayPin = relayPin;
    pinMode(relayPin, OUTPUT);
}

SteeringMotor::~SteeringMotor() {
   delete motor;
}

void SteeringMotor::setSpeed(int speed) {
    digitalWrite(this->motorRelayPin, speed != 0 ? HIGH : LOW);
    motor->setSpeed(speed);
}







