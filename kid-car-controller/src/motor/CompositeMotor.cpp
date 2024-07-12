#include "CompositeMotor.h"
#include "WString.h"
#include "../log/AbstractLogger.h"

CompositeMotor::CompositeMotor(AbstractMotor** motors, int count, AbstractLogger* logger) {
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
    logger->info("Commanded Speed: " + String(speed));
    for(int i = 0; i < count; i++) {
        motors[i]->setSpeed(speed);
    }
}