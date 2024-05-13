#include "NullMotor.h"
#include <SoftwareSerial.h>

void NullMotor::setSpeed(int speed) {
    Serial.println("Commanded Speed: " + String(speed));
}