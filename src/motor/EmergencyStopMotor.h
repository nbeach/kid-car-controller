#ifndef EmergencyStopMotor_h
#define EmergencyStopMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class EmergencyStopMotor : public AbstractMotor {
    private:
        AbstractMotor* baseMotor;
        bool stop = false;
        int lastCommandedSpeed = 0;

    public:
        EmergencyStopMotor(AbstractMotor* baseMotor);
        void setSpeed(int speed);
        bool toggleEmergencyStop();
};

#endif