#include "NullMotor.h"
#include "Wstring.h"

NullMotor::NullMotor(AbstractLogger* logger) {
    this->logger = logger;
}

void NullMotor::setSpeed(int speed) {
    logger->info("Commanded Speed: " + String(speed));
    this->speed = speed;
}

int NullMotor::getSpeed() {
    return this->speed;
}