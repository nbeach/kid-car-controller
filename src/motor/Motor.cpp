#include "Motor.h"

#include "AbstractMotor.h"
#include <SoftwareSerial.h>

Motor::Motor(int pin1, int pin2) {
    motor = new CytronMD(PWM_DIR, pin1, pin2);
}

int Motor::setSpeed(int speed) {
    Serial.println("Commanded Speed: " + String(speed));
    motor->setSpeed(speed);
    return speed;
}







