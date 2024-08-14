#ifndef AbstractMotor_h
#define AbstractMotor_h

#include <Arduino.h>

class AbstractMotor {
public:
  virtual void setSpeed(int speed);
};

#endif