#include "PriorityCompositeThrottle.h"

PriorityCompositeThrottle::PriorityCompositeThrottle(AbstractThrottle* primary, AbstractThrottle* secondary) {
    this->primary = primary;
    this->secondary = secondary;
}

PriorityCompositeThrottle::~PriorityCompositeThrottle() {
    delete primary;
    delete secondary;
}

void PriorityCompositeThrottle::onPositionChange(void (*callback)(int)) {
    this->callback = callback;
}

int PriorityCompositeThrottle::getPosition() {
    int primaryPosition = primary->getPosition();
    int secondaryPosition = secondary->getPosition();

    if(primaryPosition != 0 || secondaryDisabled) return primaryPosition;
    else return secondaryPosition;
}

void PriorityCompositeThrottle::poll() {
    int position = getPosition();
    if(position != priorPosition && callback != NULL) {
        priorPosition = position;
        callback(position);
    }
}

bool PriorityCompositeThrottle::toggleDisableSecondary() {
    secondaryDisabled = !secondaryDisabled;
    return secondaryDisabled;
}