#ifndef SteeringMotor_h
#define SteeringMotor_h

#include "AbstractMotor.h"
#include "Motor.h"

class SteeringMotor : public AbstractMotor {
  Motor *motor;
  uint8_t relayPin;

public:
  SteeringMotor(uint8_t pwmPin, uint8_t directionPin, uint8_t relayPin, int pwmFrequency);
  ~SteeringMotor() override;
  void setSpeed(int speed);
};

#endif