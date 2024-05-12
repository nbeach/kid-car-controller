#ifndef AbstractMotor_h
#define AbstractMotor_h

#include "Arduino.h"

class AbstractMotor {
    public:
        virtual int setSpeed(int speed);
};

#endif