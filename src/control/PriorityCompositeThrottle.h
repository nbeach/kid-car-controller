#ifndef PriorityCompositeThrottle_h
#define PriorityCompositeThrottle_h

#include "Arduino.h"
#include "AbstractThrottle.h"

typedef void(*priorityCompositeThrottleCallback)(int);

class PriorityCompositeThrottle : public AbstractThrottle {
    private:
    AbstractThrottle* primary;
    AbstractThrottle* secondary;
    priorityCompositeThrottleCallback callback = NULL;
    bool secondaryDisabled = true;

    int priorPosition = 0;

    public:
        PriorityCompositeThrottle(AbstractThrottle* primary, AbstractThrottle* secondary);
        void onPositionChange(void (*func)(int));
        int getPosition();
        void poll();
        bool toggleDisableSecondary();
};

#endif