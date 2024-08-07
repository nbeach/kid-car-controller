#ifndef CompositeMotor_h
#define CompositeMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"
#include "../logging/Logger.h"

class CompositeMotor : public AbstractMotor {
    private:
        AbstractMotor** motors;
        int count;
        Logger* logger;

    public:
        CompositeMotor(AbstractMotor** motors, int count, Logger* logger);
        ~CompositeMotor();
        void setSpeed(int speed);
};

#endif