#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include <stdint.h>
#include "AbstractMotor.h"
#include "../vendor/AVR_PWM.h"

class Motor : public AbstractMotor {
    private:
        uint8_t pwmPin;
        uint8_t directionPin;
        int pwmFrequency;
        AVR_PWM* pwmControl;

    public:
        Motor(uint8_t pwmPin, uint8_t directionPin, int pwmFrequency);
        ~Motor();
        void setSpeed(int speed);
};

#endif