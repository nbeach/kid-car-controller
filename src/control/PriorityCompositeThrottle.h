#ifndef PriorityCompositeThrottle_h
#define PriorityCompositeThrottle_h

#include "AbstractThrottle.h"

class PriorityCompositeThrottle : public AbstractThrottle {
  AbstractThrottle *primary;
  AbstractThrottle *secondary;
  void (*callback)(int) = nullptr;
  bool secondaryDisabled = false;
  int priorPosition = 0;

public:
  PriorityCompositeThrottle(AbstractThrottle *primary, AbstractThrottle *secondary);
  ~PriorityCompositeThrottle() override;
  void onPositionChange(void (*func)(int));
  int getPosition() override;
  void poll();
  bool toggleDisableSecondary();
};

#endif