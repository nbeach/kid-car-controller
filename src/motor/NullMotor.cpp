#include "NullMotor.h"

NullMotor::NullMotor(Logger* logger) {
    this->logger = logger;
}

void NullMotor::setSpeed(int speed) {
    this->logger->info("Commanded Speed: " + String(speed));
}