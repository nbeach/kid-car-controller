#ifndef ManualThrottle_h
#define ManualThrottle_h

#include "Arduino.h"

typedef void(*throttleCallback)(int);

class ManualThrottle {
    private:
        int throttlePin;
        int forwardPin;
        int reversePin;
        int lastThrottlePosition = 0;
        int direction = 1;
        throttleCallback callback;

    public:
        ManualThrottle(int throttlePin, int forwardPin, int reversePin);
        void onChange(void (*func)(int));
        void poll();
        int getPosition();
};

#endif