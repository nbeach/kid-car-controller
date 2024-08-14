#ifndef NullMotor_h
#define NullMotor_h

#include "../logging/AbstractLogger.h"
#include "AbstractMotor.h"

class NullMotor : public AbstractMotor {
  AbstractLogger *logger;

public:
  explicit NullMotor(AbstractLogger *logger);
  void setSpeed(int speed) override;
};

#endif