#ifndef SteeringMotor_h
#define SteeringMotor_h

#include "AbstractMotor.h"
#include <stdint.h>

class SteeringMotor : public AbstractMotor {
  uint8_t pwmPin;
  uint8_t directionPin;
  uint8_t relayPin;

public:
  SteeringMotor(uint8_t pwmPin, uint8_t directionPin, uint8_t relayPin);
  void setSpeed(int speed);
};

#endif