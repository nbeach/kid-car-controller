#ifndef SpeedLimitSelector_h
#define SpeedLimitSelector_h

#include "Arduino.h"

typedef void(*speedLimitSelectorCallback)(int);

class SpeedLimitSelector {
    private:
        speedLimitSelectorCallback callback;
        int speedLimitCount = 5;
        int speedLimits[5] = { 64, 88, 112, 184, 256 };
        int currentSpeedLimitIndex = 2;
        void emitChange();

    public:
        void onChange(void (*func)(int));
        bool increase();
        bool decrease();
        int currentLimit();
};

#endif