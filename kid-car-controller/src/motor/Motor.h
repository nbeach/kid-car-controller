#ifndef Motor_h
#define Motor_h

#include "AbstractMotor.h"
#include "../vendor/CytronMotorDriver.h"

class Motor : public AbstractMotor {
    private:
        CytronMD* motor;

    public:
        Motor(int pin1, int pin2);
        ~Motor();
        void setSpeed(int speed);
};

#endif