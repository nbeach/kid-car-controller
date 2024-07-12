#ifndef ThrottlePedal_h
#define ThrottlePedal_h

#include "AbstractThrottle.h"

class ThrottlePedal : public AbstractThrottle {
    private:
        int throttlePin;
        int forwardPin;
        int reversePin;
        int zeroThrottleReading = 1000;
        int throttlePosition();
        int direction();

    public:
        ThrottlePedal(int throttlePin, int forwardPin, int reversePin);
        int getPosition();
};

#endif