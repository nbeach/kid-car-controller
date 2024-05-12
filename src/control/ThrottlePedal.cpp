#include "ThrottlePedal.h"

#include "Arduino.h"
#include <SoftwareSerial.h>

ThrottlePedal::ThrottlePedal(int throttlePin, int forwardPin, int reversePin) {
    this->throttlePin = throttlePin;
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;
    this->callback = NULL;

    int positionAtInit = getPosition();
    if(positionAtInit != 0) {
        fault = true;
        Serial.println("Throttle pedal fault. Initial position not zero. Position is: " + String(positionAtInit));
    }
}

int ThrottlePedal::getPosition() {
    if(fault) return 0;
    int pinValue = analogRead(throttlePin);
    int withZeroMinimum = pinValue < 175 ? 0 : pinValue - 175;
    int withClippedMaximum = withZeroMinimum > 500 ? 500 : withZeroMinimum;
    int throttlePosition = (withClippedMaximum / 5) * 2.56 * direction ;
    return throttlePosition;
}
