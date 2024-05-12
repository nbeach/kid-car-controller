#ifndef AbstractThrottle_h
#define AbstractThrottle_h

#include "Arduino.h"

class AbstractThrottle {
    public:
        virtual int getPosition();
};

#endif