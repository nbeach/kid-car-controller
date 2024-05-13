#ifndef AccelerationRampingSelector_h
#define AccelerationRampingSelector_h

#include "Arduino.h"

typedef void(*accelerationRampingSelectorCallback)(double);

class AccelerationRampingSelector {
    private:
        accelerationRampingSelectorCallback callback;
        int settingCount = 5;
        double settings[5] = { 0.0001, 0.0003, 0.001, 0.005, 0.1 };
        int currentSettingIndex = 2;
        void emitChange();

    public:
        void onChange(void (*func)(double));
        bool increase();
        bool decrease();
        double currentSetting();
};

#endif