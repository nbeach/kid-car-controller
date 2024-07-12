#ifndef SteeringMotor_h
#define SteeringMotor_h

#include "AbstractMotor.h"
#include "../vendor/CytronMotorDriver.h"

class SteeringMotor : public AbstractMotor {
    private:
        AbstractMotor* motor;
        int motorRelayPin;

    public:
        SteeringMotor(AbstractMotor* motor, int relayPin);
        ~SteeringMotor();
        void setSpeed(int speed);
};

#endif