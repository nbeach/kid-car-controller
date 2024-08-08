#include "Motor.h"
#include "AbstractMotor.h"

Motor::Motor(int pwmPin, int directionPin, int pwmFrequency) {
    this->pwmPin = pwmPin;
    this->directionPin = directionPin;
    this->pwmFrequency = pwmFrequency;
    this->pwmControl = new AVR_PWM(pwmPin, pwmFrequency, 0);

    digitalWrite(pwmPin, LOW);
    digitalWrite(directionPin, LOW);
}

Motor::~Motor() {
   delete pwmControl;
}

void Motor::setSpeed(int speed) {
    if (speed > 255) {
        speed = 255;
    } else if (speed < -255) {
        speed = -255;
    }

    pwmControl->setPWM(pwmPin, pwmFrequency, (speed >= 0 ? speed : -speed) / 255 * 100);
    digitalWrite(directionPin, speed >= 0 ? LOW : HIGH);
}







