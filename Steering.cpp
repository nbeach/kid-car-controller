#include "CytronMotorDriver.h"

class Steering {
    CytronMD steeringMotor = CytronMD(PWM_DIR, 11, 13);

    public:
    void moveSteering(int direction) {
        steeringMotor.setSpeed(direction);
    }
};