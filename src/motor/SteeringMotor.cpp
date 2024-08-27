#include "SteeringMotor.h"
#include <Arduino.h>

SteeringMotor::SteeringMotor(uint8_t pwmPin, uint8_t directionPin, uint8_t relayPin, int pwmFrequency) {
  this->motor = new Motor(pwmPin, directionPin, pwmFrequency);
  this->relayPin = relayPin;

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

SteeringMotor::~SteeringMotor() { delete motor; }

void SteeringMotor::setSpeed(int speed) {
  this->motor->setSpeed(speed);
  digitalWrite(relayPin, speed != 0 ? HIGH : LOW);
}
