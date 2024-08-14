#ifndef PriorityCompositeThrottle_h
#define PriorityCompositeThrottle_h

#include "AbstractThrottle.h"
#include <Arduino.h>

class PriorityCompositeThrottle : public AbstractThrottle {
private:
  AbstractThrottle *primary;
  AbstractThrottle *secondary;
  void (*callback)(int) = NULL;
  bool secondaryDisabled = false;
  int priorPosition = 0;

public:
  PriorityCompositeThrottle(AbstractThrottle *primary,
                            AbstractThrottle *secondary);
  ~PriorityCompositeThrottle();
  void onPositionChange(void (*func)(int));
  int getPosition();
  void poll();
  bool toggleDisableSecondary();
};

#endif