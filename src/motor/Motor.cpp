#include "Motor.h"

#include "AbstractMotor.h"
#include <SoftwareSerial.h>

Motor::Motor(int pin1, int pin2) {
    motor = new CytronMD(PWM_DIR, pin1, pin2);
}

void Motor::setSpeed(int speed) {
    motor->setSpeed(speed);
}







