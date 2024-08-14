#include "SteeringMotor.h"

SteeringMotor::SteeringMotor(uint8_t pwmPin, uint8_t directionPin,
                             uint8_t relayPin) {
  this->pwmPin = pwmPin;
  this->directionPin = directionPin;
  this->relayPin = relayPin;

  pinMode(relayPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite(pwmPin, LOW);
  digitalWrite(directionPin, LOW);
}

void SteeringMotor::setSpeed(int speed) {
  if (speed > 255) {
    speed = 255;
  } else if (speed < -255) {
    speed = -255;
  }

  analogWrite(pwmPin, speed >= 0 ? speed : -speed);
  digitalWrite(directionPin, speed >= 0 ? LOW : HIGH);
  digitalWrite(relayPin, speed != 0 ? HIGH : LOW);
}
