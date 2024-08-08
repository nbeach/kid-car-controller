#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include "AbstractMotor.h"
#include "../vendor/AVR_PWM.h"

class Motor : public AbstractMotor {
    private:
        int pwmPin;
        int directionPin;
        int pwmFrequency;
        AVR_PWM* pwmControl;

    public:
        Motor(int pwmPin, int directionPin, int pwmFrequency);
        ~Motor();
        void setSpeed(int speed);
};

#endif