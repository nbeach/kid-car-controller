#ifndef ThrottlePedal_h
#define ThrottlePedal_h

#include "Arduino.h"
#include "AbstractThrottle.h"
#include "../logging/Logger.h"

class ThrottlePedal : public AbstractThrottle {
    private:
        int throttlePin;
        int forwardPin;
        int reversePin;
        int zeroThrottleReading = 1000;
        int throttlePosition();
        int direction();
        Logger* logger;

    public:
        ThrottlePedal(int throttlePin, int forwardPin, int reversePin, Logger* logger);
        int getPosition();
};

#endif