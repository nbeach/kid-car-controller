#ifndef ThrottlePedal_h
#define ThrottlePedal_h

#include "Arduino.h"
#include "AbstractThrottle.h"

typedef void(*throttleCallback)(int);

class ThrottlePedal : public AbstractThrottle {
    private:
        int throttlePin;
        int forwardPin;
        int reversePin;
        int lastThrottlePosition = 0;
        int direction = 1;
        throttleCallback callback;
        int fault = false;

    public:
        ThrottlePedal(int throttlePin, int forwardPin, int reversePin);
        int getPosition();
};

#endif