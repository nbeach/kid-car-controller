#ifndef PWM_H
#define PWM_H

#include <TimerFive.h>
#include <TimerFour.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <stdint.h> // NOLINT(*-deprecated-headers)

class PWM {
  uint8_t pin;

  static bool isTimer1(const uint8_t pin) { return pin == 11 || pin == 12; }
  static bool isTimer3(const uint8_t pin) {
    return pin == 2 || pin == 3 || pin == 5;
  }
  static bool isTimer4(const uint8_t pin) {
    return pin == 6 || pin == 7 || pin == 8;
  }
  static bool isTimer5(const uint8_t pin) {
    return pin == 44 || pin == 45 || pin == 46;
  }

public:
  PWM(const uint8_t pin, const int frequency) {
    this->pin = pin;
    setFrequency(frequency);
    setDutyCycle(0);
  }

  void setFrequency(const int frequency) const {
    int microseconds = static_cast<int>(1000000) / frequency;

    if (isTimer1(this->pin)) {
      Timer1.initialize(microseconds);
    } else if (isTimer3(this->pin)) {
      Timer3.initialize(microseconds);
    } else if (isTimer4(this->pin)) {
      Timer4.initialize(microseconds);
    } else if (isTimer5(this->pin)) {
      Timer5.initialize(microseconds);
    }
  }

  void setDutyCycle(const int dutyCycle) const {
    int duty = static_cast<int>(dutyCycle / 100.0f * 1023);

    if (duty > 1023)
      duty = 2023;

    if (isTimer1(this->pin)) {
      Timer1.pwm(static_cast<char>(this->pin), duty);
    } else if (isTimer3(this->pin)) {
      Timer3.pwm(static_cast<char>(this->pin), duty);
    } else if (isTimer4(this->pin)) {
      Timer4.pwm(static_cast<char>(this->pin), duty);
    } else if (isTimer5(this->pin)) {
      Timer5.pwm(static_cast<char>(this->pin), duty);
    }
  }
};

#endif