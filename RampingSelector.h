#ifndef RampingSelector_h
#define RampingSelector_h

#include "Arduino.h"

class RampingSelector {
    private:
        int rampingRateCount = 5;
        double rampingRates[5] = { 0.0001, 0.0005, 0.001, 0.002, 0.003 };
        int currentRampingRateIndex = 2;

    public:
        double increase();
        double decrease();
        double currentRate();
};

#endif