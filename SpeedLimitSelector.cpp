#include "SpeedLimitSelector.h"

int SpeedLimitSelector::increase() {
    if(currentSpeedLimitIndex < (speedLimitCount - 1)) currentSpeedLimitIndex++;
    return currentLimit();
}

int SpeedLimitSelector::decrease() {
    if(currentSpeedLimitIndex > 0) currentSpeedLimitIndex--;
    return currentLimit();
}

int SpeedLimitSelector::currentLimit() {
    return speedLimits[currentSpeedLimitIndex];
}
