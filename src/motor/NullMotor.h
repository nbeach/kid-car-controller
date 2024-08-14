#ifndef NullMotor_h
#define NullMotor_h

#include "../logging/AbstractLogger.h"
#include "AbstractMotor.h"
#include <Arduino.h>

class NullMotor : public AbstractMotor {
private:
  AbstractLogger *logger;

public:
  NullMotor(AbstractLogger *logger);
  void setSpeed(int speed);
};

#endif