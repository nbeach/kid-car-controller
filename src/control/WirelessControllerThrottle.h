#ifndef WirelessControllerThrottle_h
#define WirelessControllerThrottle_h

#include "AbstractThrottle.h"
#include "WirelessController.h"
#include <Arduino.h>

class WirelessControllerThrottle : public AbstractThrottle {
private:
  WirelessController *controller;
  int throttleAxis;

public:
  WirelessControllerThrottle(WirelessController *controller, int throttleAxis);
  ~WirelessControllerThrottle();
  int getPosition();
};

#endif