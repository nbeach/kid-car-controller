#include "ThrottlePedal.h"

#include "Arduino.h"
#include <SoftwareSerial.h>

ThrottlePedal::ThrottlePedal(int throttlePin, int forwardPin, int reversePin) {
    pinMode(throttlePin, INPUT);
    pinMode(forwardPin, INPUT);
    pinMode(reversePin, INPUT);

    this->throttlePin = throttlePin;
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;
    this->zeroThrottleReading = analogRead(throttlePin) + 100;
}

int ThrottlePedal::throttlePosition() {
    int pinValue = analogRead(throttlePin);
    int withZeroMinimum = pinValue < zeroThrottleReading ? 0 : pinValue - zeroThrottleReading;
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
    return throttlePosition() * direction();
}
