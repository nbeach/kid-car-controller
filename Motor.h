#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include "AbstractMotor.h"
#include "CytronMotorDriver.h"

class Motor : public AbstractMotor {
    private:
        CytronMD* motor;

    public:
        Motor(int pin1, int pin2);
        int setSpeed(int speed);
};

#endif