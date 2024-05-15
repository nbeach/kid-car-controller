#ifndef PriorityCompositeThrottle_h
#define PriorityCompositeThrottle_h

#include "Arduino.h"
#include "AbstractThrottle.h"

class PriorityCompositeThrottle : public AbstractThrottle {
    private:
    AbstractThrottle* primary;
    AbstractThrottle* secondary;
    void (*callback)(int) = NULL;
    bool secondaryDisabled = true;

    int priorPosition = 0;

    public:
        PriorityCompositeThrottle(AbstractThrottle* primary, AbstractThrottle* secondary);
        ~PriorityCompositeThrottle();
        void onPositionChange(void (*func)(int));
        int getPosition();
        void poll();
        bool toggleDisableSecondary();
};

#endif