#ifndef NullMotor_h
#define NullMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class NullMotor : public AbstractMotor {
    public:
        int setSpeed(int speed);
};

#endif