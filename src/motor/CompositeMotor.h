#ifndef CompositeMotor_h
#define CompositeMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"
#include "../vendor/CytronMotorDriver.h"

class CompositeMotor : public AbstractMotor {
    private:
        CytronMD frontLeftMotor = CytronMD(PWM_DIR, 5, 4);
        CytronMD frontRightMotor = CytronMD(PWM_DIR, 10, 12);
        CytronMD rearLeftMotor = CytronMD(PWM_DIR, 3, 2);
        CytronMD rearRightMotor = CytronMD(PWM_DIR, 6, 7);

    public:
        int setSpeed(int speed);
};

#endif