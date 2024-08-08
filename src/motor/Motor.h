#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include <stdint.h>
#include "AbstractMotor.h"

class Motor : public AbstractMotor {
    private:
        uint8_t pwmPin;
        uint8_t directionPin;

    public:
        Motor(uint8_t pwmPin, uint8_t directionPin);
        void setSpeed(int speed);
};

#endif