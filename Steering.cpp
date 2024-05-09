#include "CytronMotorDriver.h"

class Steering {
    CytronMD* steeringMotor;

public:
    Steering() {
      steeringMotor = &CytronMD(PWM_DIR, 11, 13);
    }

    void moveSteering(int direction) {
        steeringMotor->setSpeed(direction);
    }
};