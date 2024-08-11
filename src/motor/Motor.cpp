#include "Motor.h"
#include "AbstractMotor.h"

Motor::Motor(uint8_t pwmPin, uint8_t directionPin) {
    this->pwmPin = pwmPin;
    this->directionPin = directionPin;

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

    analogWrite(pwmPin, speed >= 0 ? speed : -speed);
    digitalWrite(directionPin, speed >= 0 ? LOW : HIGH);
}







