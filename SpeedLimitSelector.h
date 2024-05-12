#ifndef SpeedLimitSelector_h
#define SpeedLimitSelector_h

#include "Arduino.h"

class SpeedLimitSelector {
    private:
        int speedLimitCount = 5;
        int speedLimits[5] = { 64, 88, 112, 184, 256 };
        int currentSpeedLimitIndex = 2;

    public:
        int increase();
        int decrease();
        int currentLimit();
};

#endif