#include "Motor.h"
#include "AbstractMotor.h"

Motor::Motor(uint8_t pwmPin, uint8_t directionPin, int pwmFrequency) {
    this->pwmPin = pwmPin;
    this->directionPin = directionPin;
    this->pwmFrequency = pwmFrequency;

    pinMode(pwmPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    digitalWrite(pwmPin, LOW);
    digitalWrite(directionPin, LOW);

    pwmControl = pwmFrequency == NULL ? NULL : new AVR_PWM(pwmPin, pwmFrequency, 0);
}

Motor::~Motor() {
     if(pwmControl != NULL) delete pwmControl;
}

void Motor::setSpeed(int speed) {
    if (speed > 255) {
        speed = 255;
    } else if (speed < -255) {
        speed = -255;
    }

     if(pwmControl == NULL) {
        analogWrite(pwmPin, speed >= 0 ? speed : -speed);
     } else {
        pwmControl->setPWM(pwmPin, pwmFrequency, (speed >= 0 ? speed : -speed) / 255.0f * 100);
     }

    digitalWrite(directionPin, speed >= 0 ? LOW : HIGH);
}







