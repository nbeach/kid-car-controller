#ifndef CompositeMotor_h
#define CompositeMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"

class CompositeMotor : public AbstractMotor {
    private:
        AbstractMotor** motors;
        int count;

    public:
        CompositeMotor(AbstractMotor** motors, int count);
        void setSpeed(int speed);
};

#endif