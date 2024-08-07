#include "ThrottlePedal.h"

ThrottlePedal::ThrottlePedal(int throttlePin, int forwardPin, int reversePin, Logger* logger) {
    pinMode(throttlePin, INPUT);
    pinMode(forwardPin, INPUT_PULLUP);
    pinMode(reversePin, INPUT_PULLUP);

    this->throttlePin = throttlePin;
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;
    this->zeroThrottleReading = analogRead(throttlePin) + 100;
    this->logger = logger;
}

int ThrottlePedal::throttlePosition() {
    int pinValue = analogRead(throttlePin);
    int withZeroMinimum = pinValue < zeroThrottleReading ? 0 : pinValue - zeroThrottleReading;
    int withClippedMaximum = withZeroMinimum > 500 ? 500 : withZeroMinimum;
    int throttlePosition = (withClippedMaximum / 5) * 2.56;

    return throttlePosition;
}

int ThrottlePedal::direction() {
    this->logger->info("forwardPin: " + String(digitalRead(forwardPin)) + " - reversePin: " + String(digitalRead(reversePin)) + " - throttle: " + String(analogRead(throttlePin)));
    if(digitalRead(forwardPin) == LOW) {
        return 1;
    } else if(digitalRead(reversePin) == LOW) {
        return -1;
    } else {
        return 0;
    }
}

int ThrottlePedal::getPosition() {
    return throttlePosition() * direction();
}
