#ifndef SpeedLimitedMotor_h
#define SpeedLimitedMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class SpeedLimitedMotor : public AbstractMotor {
    private:
        AbstractMotor* baseMotor;
        int speedLimit = 256;

    public:
        SpeedLimitedMotor(AbstractMotor* baseMotor);
        void setSpeed(int speed);
        void setSpeedLimit(int limit);
};

#endif