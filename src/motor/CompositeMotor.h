#ifndef CompositeMotor_h
#define CompositeMotor_h

#include "../logging/AbstractLogger.h"
#include "AbstractMotor.h"

class CompositeMotor : public AbstractMotor {
  AbstractMotor **motors;
  int count;
  AbstractLogger *logger;

public:
  CompositeMotor(AbstractMotor **motors, int count, AbstractLogger *logger);
  ~CompositeMotor();
  void setSpeed(int speed);
};

#endif