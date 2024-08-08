#ifndef NullMotor_h
#define NullMotor_h

#include <Arduino.h>
#include "AbstractMotor.h"
#include "../logging/AbstractLogger.h"

class NullMotor : public AbstractMotor {
    private:
        AbstractLogger* logger;

    public:
        NullMotor(AbstractLogger* logger);
        void setSpeed(int speed);
};

#endif