#include "AccelerationRampingSelector.h"

#include "Arduino.h"

void AccelerationRampingSelector::onChange(void (*func)(double)) {
    this->callback = func;
}

void AccelerationRampingSelector::emitChange() {
    if(callback != NULL) callback(settings[currentSettingIndex]);
}

bool AccelerationRampingSelector::increase() {
    if(currentSettingIndex < (settingCount - 1)) {
        currentSettingIndex++;
        emitChange();
        return true;
    }
    return false;
}

bool AccelerationRampingSelector::decrease() {
    if(currentSettingIndex > 0) {
        currentSettingIndex--;
        emitChange();
        return true;
    }
    return false;
}

double AccelerationRampingSelector::currentSetting() {
    return settings[currentSettingIndex];
}
