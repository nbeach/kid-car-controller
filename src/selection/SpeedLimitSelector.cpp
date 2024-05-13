#include "SpeedLimitSelector.h"

#include "Arduino.h"

void SpeedLimitSelector::onChange(void (*func)(int)) {
    this->callback = func;
}

void SpeedLimitSelector::emitChange() {
    if(callback != NULL) callback(speedLimits[currentSpeedLimitIndex]);
}

bool SpeedLimitSelector::increase() {
    if(currentSpeedLimitIndex < (speedLimitCount - 1)) {
        currentSpeedLimitIndex++;
        emitChange();
        return true;
    }
    return false;
}

bool SpeedLimitSelector::decrease() {
    if(currentSpeedLimitIndex > 0) {
        currentSpeedLimitIndex--;
        emitChange();
        return true;
    }
    return false;
}

int SpeedLimitSelector::currentLimit() {
    return speedLimits[currentSpeedLimitIndex];
}
