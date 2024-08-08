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

    if (speed >= 0) {
        analogWrite(this->pwmPin, speed);
        digitalWrite(this->directionPin, LOW);
    } else {
        analogWrite(this->pwmPin, -speed);
        digitalWrite(this->directionPin, HIGH);
    }
    digitalWrite(this->relayPin, speed != 0 ? HIGH : LOW);
}







