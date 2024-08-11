#ifndef PWM_H
#define PWM_H

#include <Arduino.h>
#include <stdint.h>
#include "../vendor/TimerOne/TimerOne.h"
#include "../vendor/TimerThree/TimerThree.h"
#include "../vendor/TimerFour/TimerFour.h"
#include "../vendor/TimerFive/TimerFive.h"

class PWM {
    private:
    uint8_t pin;

    bool isTimer1(uint8_t pin) { return pin == 11 || pin == 12; }
    bool isTimer3(uint8_t pin) { return pin == 2 || pin == 3 || pin == 5; }
    bool isTimer4(uint8_t pin) { return pin == 6 || pin == 7 || pin == 8; }
    bool isTimer5(uint8_t pin) { return pin == 44 || pin == 45 || pin == 46; }

    public:
    PWM(uint8_t pin, int frequency) {
       this->pin = pin;
       setFrequency(frequency);
       setDutyCycle(0);
    }

    void setFrequency(int frequency) {
        int microseconds = 1000000.0f / frequency;

        if(isTimer1(this->pin)) {
            Timer1.initialize(microseconds);
        } else if(isTimer3(this->pin)) {
            Timer3.initialize(microseconds);
        } else if(isTimer4(this->pin)) {
            Timer4.initialize(microseconds);
        } else if(isTimer5(this->pin)) {
            Timer5.initialize(microseconds);
        }
    }

    void setDutyCycle(int dutyCycle) {
        int duty = (dutyCycle / 100.0f) * 1023;

        if(duty > 1023) duty = 2023;

        if(isTimer1(this->pin)) {
            Timer1.pwm(this->pin, duty);
        } else if(isTimer3(this->pin)) {
            Timer3.pwm(this->pin, duty);
        } else if(isTimer4(this->pin)) {
            Timer4.pwm(this->pin, duty);
        } else if(isTimer5(this->pin)) {
            Timer5.pwm(this->pin, duty);
        }
    }
};

#endif