#include "CompositeMotor.h"

#include "Arduino.h"

CompositeMotor::CompositeMotor(AbstractMotor** motors, int count, Logger* logger) {
    this->motors = motors;
    this->count = count;
    this->logger = logger;
}

CompositeMotor::~CompositeMotor() {
    for(int i = 0; i < count; i++) {
        delete motors[i];
    }
    delete[] motors;
}

void CompositeMotor::setSpeed(int speed) {
    this->logger->info("Commanded Speed: " + String(speed));
    for(int i = 0; i < count; i++) {
        motors[i]->setSpeed(speed);
    }
}