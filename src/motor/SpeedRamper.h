#ifndef SpeedRamper_h
#define SpeedRamper_h

#include "Arduino.h"

class SpeedRamper {
    private:
    double accelerationRampingRate;
    double decelerationRampingRate;
    int initialSpeed = 0;
    int currentSpeed = 0;
    int targetSpeed = 0;
    int timeCurrentSpeedSet = 0;


    public:
    SpeedRamper(double accelerationRampingRate, double decelerationRampingRate);
    void setTargetSpeed(int speed);
    void setCurrentSpeed(int speed);
    int getCurrentSpeed();
    void setAccelerationRate(double rate);
    void setDecelerationRate(double rate);
    void tick();
};

#endif