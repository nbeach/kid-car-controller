#include "Motor.h"

#include "AbstractMotor.h"

Motor::Motor(int pin1, int pin2) {
    motor = new CytronMD(PWM_DIR, pin1, pin2);
}

Motor::~Motor() {
   delete motor;
}

void Motor::setSpeed(int speed) {
    motor->setSpeed(speed);
}







