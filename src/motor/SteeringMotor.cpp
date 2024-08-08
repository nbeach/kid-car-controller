#include "SteeringMotor.h"

SteeringMotor::SteeringMotor(int pwmPin, int directionPin, int relayPin) {
    this->pwmPin = pwmPin;
    this->directionPin = directionPin;
    this->relayPin = relayPin;
    pinMode(relayPin, OUTPUT);
}

void SteeringMotor::setSpeed(int speed) {
    if (speed > 255) {
        speed = 255;
    } else if (speed < -255) {
        speed = -255;
    }

    analogWrite(pwmPin, speed >= 0 ? speed : -speed);
    digitalWrite(directionPin, speed >= 0 ? LOW : HIGH);
    digitalWrite(relayPin, speed != 0 ? HIGH : LOW);
}







