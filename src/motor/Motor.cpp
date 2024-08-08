#include "Motor.h"
#include "AbstractMotor.h"

Motor::Motor(int pwmPin, int directionPin, int pwmFrequency) {
    this->pwmPin = pwmPin;
    this->directionPin = directionPin;
    this->pwmFrequency = pwmFrequency;

    pinMode(pwmPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    digitalWrite(pwmPin, LOW);
    digitalWrite(directionPin, LOW);
}

void Motor::setSpeed(int speed) {
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
}







