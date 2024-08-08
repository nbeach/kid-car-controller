#ifndef WirelessControllerThrottle_h
#define WirelessControllerThrottle_h

#include <Arduino.h>
#include "AbstractThrottle.h"
#include "WirelessController.h"

class WirelessControllerThrottle : public AbstractThrottle {
    private:
    WirelessController* controller;
    int throttleAxis;

    public:
        WirelessControllerThrottle(WirelessController* controller, int throttleAxis);
        ~WirelessControllerThrottle();
        int getPosition();
};

#endif