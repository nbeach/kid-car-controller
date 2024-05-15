#ifndef ThrottlePedal_h
#define ThrottlePedal_h

#include "Arduino.h"
#include "AbstractThrottle.h"

class ThrottlePedal : public AbstractThrottle {
    private:
        int throttlePin;
        int forwardPin;
        int reversePin;
        int fault = false;
        int throttlePosition();
        int direction();

    public:
        ThrottlePedal(int throttlePin, int forwardPin, int reversePin);
        int getPosition();
};

#endif