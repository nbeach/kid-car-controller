#include "NullMotor.h"

NullMotor::NullMotor(AbstractLogger *logger) { this->logger = logger; }

void NullMotor::setSpeed(int speed) { this->logger->info("Commanded Speed: " + String(speed)); }