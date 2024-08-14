#ifndef Motor_h
#define Motor_h

#include "../pwm/PWM.h"
#include "AbstractMotor.h"
#include <stdint.h>

class Motor : public AbstractMotor {
  uint8_t pwmPin;
  uint8_t directionPin;
  int pwmFrequency;
  PWM *pwmControl;

public:
  Motor(uint8_t pwmPin, uint8_t directionPin, int pwmFrequency);
  ~Motor();
  void setSpeed(int speed);
};

#endif