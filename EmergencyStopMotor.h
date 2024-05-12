#ifndef EmergencyStopMotor_h
#define EmergencyStopMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class EmergencyStopMotor : public AbstractMotor {
    private:
        AbstractMotor* baseMotor;
        bool stop = false;

    public:
        EmergencyStopMotor(AbstractMotor* baseMotor);
        int setSpeed(int speed);
        void toggleEmergencyStop();
};

#endif