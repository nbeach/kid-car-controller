#ifndef RampingSpeedLimitedEmergencyStopMotor_h
#define RampingSpeedLimitedEmergencyStopMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"
#include "EmergencyStopMotor.h"
#include "SpeedLimitedMotor.h"
#include "RampingMotor.h"

class RampingSpeedLimitedEmergencyStopMotor : public AbstractMotor {
    private:
        EmergencyStopMotor* emergencyStopMotor;
        SpeedLimitedMotor* speedLimitedMotor;
        RampingMotor* rampingMotor;

    public:
        RampingSpeedLimitedEmergencyStopMotor(AbstractMotor* baseMotor);
        void setSpeed(int speed);
        void setRampingRate(double rampingRate);
        void setSpeedLimit(int limit);
        bool toggleEmergencyStop();
        void tick();
};

#endif