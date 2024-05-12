#include "NullMotor.h"
#include <SoftwareSerial.h>

int NullMotor::setSpeed(int speed) {
    Serial.println("Commanded Speed: " + String(speed));
    return speed;
}