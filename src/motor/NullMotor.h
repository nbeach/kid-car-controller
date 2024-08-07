#ifndef NullMotor_h
#define NullMotor_h

#include "Arduino.h"
#include "AbstractMotor.h"
#include "../logging/Logger.h"

class NullMotor : public AbstractMotor {
    private:
    Logger*  logger;

    public:
    NullMotor(Logger* logger);
    void setSpeed(int speed);
};

#endif