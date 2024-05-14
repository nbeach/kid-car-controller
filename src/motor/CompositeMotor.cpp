#include "CompositeMotor.h"

#include "Arduino.h"
#include <SoftwareSerial.h>

CompositeMotor::CompositeMotor(AbstractMotor** motors, int count) {
    this->motors = motors;
    this->count = count;
}

void CompositeMotor::setSpeed(int speed) {
    Serial.println("Commanded Speed: " + String(speed));
    for(int i = 0; i < count; i++) {
        motors[i]->setSpeed(speed);
    }
}