#include "WirelessControllerThrottle.h"

#include "Arduino.h"

WirelessControllerThrottle::WirelessControllerThrottle(WirelessController* controller, int throttleAxis) {
    this->controller = controller;
    this->throttleAxis = throttleAxis;
}

int WirelessControllerThrottle::getPosition() {
    return controller->getAxisState(throttleAxis);
}
