#ifndef SteeringMotor_h
#define SteeringMotor_h

#include <Arduino.h>
#include "AbstractMotor.h"

class SteeringMotor : public AbstractMotor {
    private:
        int pwmPin;
        int directionPin;
        int relayPin;

    public:
        SteeringMotor(int pwmPin, int directionPin, int relayPin);
        void setSpeed(int speed);
};

#endif