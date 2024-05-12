#include "RampingSelector.h"

double RampingSelector::increase() {
    if(currentRampingRateIndex < (rampingRateCount - 1)) currentRampingRateIndex++;
    return currentRate();
}

double RampingSelector::decrease() {
    if(currentRampingRateIndex > 0) currentRampingRateIndex--;
    return currentRate();
}

double RampingSelector::currentRate() {
    return rampingRates[currentRampingRateIndex];
}
