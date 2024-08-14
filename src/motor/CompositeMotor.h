#ifndef CompositeMotor_h
#define CompositeMotor_h

#include "../logging/AbstractLogger.h"
#include "AbstractMotor.h"
#include <Arduino.h>

class CompositeMotor : public AbstractMotor {
private:
  AbstractMotor **motors;
  int count;
  AbstractLogger *logger;

public:
  CompositeMotor(AbstractMotor **motors, int count, AbstractLogger *logger);
  ~CompositeMotor();
  void setSpeed(int speed);
};

#endif