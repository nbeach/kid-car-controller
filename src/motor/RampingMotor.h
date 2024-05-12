#ifndef RampingMotor_h
#define RampingMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class RampingMotor : public AbstractMotor {
    private:
        AbstractMotor* baseMotor;

        double rampingRate = 0.001;
        double decelerationRampingRate = 0.001;
        int initialSpeed = 0;
        int currentSpeed = 0;
        int targetSpeed = 0;
        int timeCurrentSpeedSet = 0;

        int setCurrentSpeed(int speed);
        void stepTowardsTargetSpeed();

    public:
        RampingMotor(AbstractMotor* baseMotor);
        int setSpeed(int speed);
        void setRampingRate(double rampingRate);
        void tick();
};

#endif