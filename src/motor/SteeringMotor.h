#ifndef SteeringMotor_h
#define SteeringMotor_h

#include <Arduino.h>
#include <stdint.h>
#include "AbstractMotor.h"

class SteeringMotor : public AbstractMotor {
    private:
        uint8_t pwmPin;
        uint8_t directionPin;
        uint8_t relayPin;

    public:
        SteeringMotor(uint8_t pwmPin, uint8_t directionPin, uint8_t relayPin);
        void setSpeed(int speed);
};

#endif