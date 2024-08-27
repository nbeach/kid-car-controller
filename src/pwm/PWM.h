#ifndef PWM_H
#define PWM_H

#include <pwm.h>
#include <stdint.h> // NOLINT(*-deprecated-headers)

class PWM {
  uint8_t pin;
  PwmOut *pwm;

public:
  PWM(const uint8_t pin, const float frequency) {
    this->pin = pin;
    this->pwm = new PwmOut(pin);
    this->pwm->begin(frequency, 0.0f);
  }

  void setDutyCycle(const float dutyCycle) const { this->pwm->pulse_perc(dutyCycle); }
};

#endif