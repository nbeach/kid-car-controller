#ifndef CompositeMotor_h
#define CompositeMotor_h

#include "AbstractMotor.h"
#include "../log/AbstractLogger.h"

class CompositeMotor : public AbstractMotor {
    private:
        AbstractMotor** motors;
        int count;
        AbstractLogger* logger;

    public:
        CompositeMotor(AbstractMotor** motors, int count, AbstractLogger* logger);
        ~CompositeMotor();
        void setSpeed(int speed) override;
};

#endif