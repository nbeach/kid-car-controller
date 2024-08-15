#ifndef WirelessControllerThrottle_h
#define WirelessControllerThrottle_h

#include "AbstractThrottle.h"
#include "WirelessController.h"

class WirelessControllerThrottle : public AbstractThrottle {
  WirelessController *controller;
  int throttleAxis;

public:
  WirelessControllerThrottle(WirelessController *controller, int throttleAxis);
  ~WirelessControllerThrottle() override;
  int getPosition() override;
};

#endif