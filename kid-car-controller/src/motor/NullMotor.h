#ifndef NullMotor_h
#define NullMotor_h

#include "AbstractMotor.h"
#include "../log/AbstractLogger.h"

class NullMotor : public AbstractMotor {
	private:
		AbstractLogger* logger;
		int speed = 0;

    public:
		NullMotor(AbstractLogger* logger);
        int getSpeed();
        void setSpeed(int speed);
};

#endif