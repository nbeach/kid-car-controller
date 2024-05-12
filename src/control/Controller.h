#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "../vendor/Cytron_PS2Shield.h"

typedef void(*buttonCallback)();
typedef void(*axisCallback)(int);

class Controller {
  protected:
  Cytron_PS2Shield ps2;
  int buttonStates[26];
  int axisStates[26];
  buttonCallback buttonCallbacks[26];
  axisCallback axisCallbacks[26];
  int vibrationStartedTime = -1;
  int vibrationDuration = 0;

  void maybeEndVibration();
  int to256Position(int rawPosition);

  public:
  Controller();
  void poll();
  void pollButtonState(int button);
  void pollAxisState(int axis);
  int getAxisState(int axis);
  void onButtonPressed(int button, void (*func)());
  void onAxisChange(int axis, void (*func)(int));
  void vibrate(int durationMilliseconds, int intensity);
};

#endif