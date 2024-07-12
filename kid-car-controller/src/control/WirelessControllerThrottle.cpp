#include "WirelessControllerThrottle.h"

WirelessControllerThrottle::WirelessControllerThrottle(WirelessController* controller, int throttleAxis) {
    this->controller = controller;
    this->throttleAxis = throttleAxis;
}

WirelessControllerThrottle::~WirelessControllerThrottle() {
    delete controller;
}

int WirelessControllerThrottle::getPosition() {
    return controller->getAxisState(throttleAxis);
}
