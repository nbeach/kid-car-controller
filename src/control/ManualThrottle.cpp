#include "ManualThrottle.h"

#include "Arduino.h"

typedef void(*throttleCallback)(int);

ManualThrottle::ManualThrottle(int throttlePin, int forwardPin, int reversePin) {
    this->throttlePin = throttlePin;
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;
    this->callback = NULL;
}

void ManualThrottle::onChange(void (*func)(int)) {
  this->callback = func;
}

void ManualThrottle::poll() {
    int pinValue = analogRead(throttlePin);
    int withZeroMinimum = pinValue < 175 ? 0 : pinValue - 175;
    int withClippedMaximum = withZeroMinimum > 500 ? 500 : withZeroMinimum;
    int throttle = (withClippedMaximum / 5) * 2.56 * direction ;

    if(throttle == lastThrottlePosition) return;

    lastThrottlePosition = throttle;
    callback(throttle);
}

int ManualThrottle::getPosition() {
  return lastThrottlePosition;
}
