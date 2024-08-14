#ifndef ThrottlePedal_h
#define ThrottlePedal_h

#include "../logging/AbstractLogger.h"
#include "AbstractThrottle.h"

class ThrottlePedal : public AbstractThrottle {
  int throttlePin;
  int forwardPin;
  int reversePin;
  int zeroThrottleReading = 1000;
  int throttlePosition();
  int direction();
  AbstractLogger *logger;

public:
  ThrottlePedal(int throttlePin, int forwardPin, int reversePin,
                AbstractLogger *logger);
  int getPosition() override;
};

#endif