#ifndef DriveMotor_h
#define DriveMotor_h

#include <Arduino.h>
#include "AbstractMotor.h"
#include "SpeedRamper.h"
#include "../logging/AbstractLogger.h"

class DriveMotor : public AbstractMotor {
    private:
        AbstractMotor* motor;
        SpeedRamper* speedRamper;
        int speedLimit = 256;
        int reverseSpeedLimit = 108;
        int commandedSpeed = 0;
        bool emergencyStopEnabled = false;
        bool isAboveLimit(int speed);
        AbstractLogger* logger;

    public:
        DriveMotor(AbstractMotor* motor, AbstractLogger* logger);
        ~DriveMotor();
        void setSpeed(int speed);
        void setSpeedLimit(int limit);
        bool toggleEmergencyStop();
        void tick();
};

#endif