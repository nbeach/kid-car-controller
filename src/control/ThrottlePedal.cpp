#include "ThrottlePedal.h"

#include "Arduino.h"
#include <SoftwareSerial.h>

ThrottlePedal::ThrottlePedal(int throttlePin, int forwardPin, int reversePin) {
    this->throttlePin = throttlePin;
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;

    pinMode(throttlePin, INPUT);
    pinMode(forwardPin, INPUT);
    pinMode(reversePin, INPUT);

    int positionAtInit = getPosition();
    if(positionAtInit != 0) {
        fault = true;
        Serial.println("Throttle pedal fault. Initial position not zero. Position is: " + String(positionAtInit));
    }
}

int ThrottlePedal::throttlePosition() {
    int pinValue = analogRead(throttlePin);
    int withZeroMinimum = pinValue < 250 ? 0 : pinValue - 250;
    int withClippedMaximum = withZeroMinimum > 500 ? 500 : withZeroMinimum;
    int throttlePosition = (withClippedMaximum / 5) * 2.56;

    return throttlePosition;
}

int ThrottlePedal::direction() {
    if(analogRead(forwardPin) < 735) {
        return 1;
    } else if(analogRead(reversePin) < 735) {
        return -1;
    } else {
        return 0;
    }
}

int ThrottlePedal::getPosition() {
    return fault ? 0 : (throttlePosition() * direction());
}
