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

    public:
    PWM(uint8_t pin, int frequency) {
       this->pin = pin;
       setFrequency(frequency);
       setDutyCycle(0);
    }

    void setFrequency(int frequency) {
        int microseconds = 1000000.0f / frequency;

        if(this->pin == 11 || this->pin == 12) {
            Timer1.initialize(microseconds);
        } else if(this->pin == 2 || this->pin == 3 || this->pin == 5) {
            Timer3.initialize(microseconds);
        } else if(this->pin == 6 || this->pin == 7 || this->pin == 8) {
            Timer4.initialize(microseconds);
        } else if(this->pin == 44 || this->pin == 45 || this->pin == 46) {
            Timer5.initialize(microseconds);
        }
    }

    void setDutyCycle(int dutyCycle) {
        int duty = (dutyCycle / 100.0f) * 1023;

        if(duty > 1023) duty = 2023;

        Serial.println(duty);
        if(this->pin == 11 || this->pin == 12) {
            Timer1.pwm(this->pin, duty);
        } else if(this->pin == 2 || this->pin == 3 || this->pin == 5) {
            Timer3.pwm(this->pin, duty);
        } else if(this->pin == 6 || this->pin == 7 || this->pin == 8) {
            Timer4.pwm(this->pin, duty);
        } else if(this->pin == 44 || this->pin == 45 || this->pin == 46) {
            Timer5.pwm(this->pin, duty);
        }
    }
};

#endif