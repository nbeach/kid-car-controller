#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class Motor : public AbstractMotor {
    private:
    int pwmPin;
    int directionPin;
    int pwmFrequency;

    public:
        Motor(int pwmPin, int directionPin, int pwmFrequency);
        void setSpeed(int speed);
};

#endif