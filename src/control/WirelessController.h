#ifndef WirelessController_h
#define WirelessController_h

#include <Arduino.h>
#include "../vendor/Cytron_PS2Shield.h"

enum {
    VIBRATION_HEAVY,
    VIBRATION_LIGHT,
};


class WirelessController {
    protected:
        Cytron_PS2Shield ps2;
        int buttonStates[26];
        int axisStates[26];
        void (*buttonCallbacks[26])();
        void (*axisCallbacks[26])(int);
        int vibrationStartedTime = -1;
        int vibrationDuration = 0;
        void maybeEndVibration();
        int to256Position(int rawPosition);

    public:
        WirelessController(uint8_t rxPin, uint8_t txPin, uint32_t baud);
        void poll();
        void pollButtonState(int button);
        void pollAxisState(int axis);
        int getAxisState(int axis);
        void onButtonPressed(int button, void (*func)());
        void onAxisChange(int axis, void (*func)(int));
        void vibrate(int level);
};

#endif