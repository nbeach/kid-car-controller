#ifndef AccelerationRampingSelector_h
#define AccelerationRampingSelector_h

#include "Arduino.h"

class AccelerationRampingSelector {
    private:
        void (*callback)(double);
        int settingCount = 5;
        // Graphed https://www.desmos.com/calculator/hmvl2r0fbx
        double settings[5] = { 0.00001, 0.00003, 0.0001, 0.0005, 0.01 };
        int currentSettingIndex = 2;
        void emitChange();

    public:
        void onChange(void (*func)(double));
        bool increase();
        bool decrease();
        double currentSetting();
};

#endif