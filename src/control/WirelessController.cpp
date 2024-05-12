#include "WirelessController.h"

#include "Arduino.h"


void WirelessController::maybeEndVibration() {
  if(vibrationStartedTime == -1) return;
  int now = millis();
  int vibrationEndTime = vibrationStartedTime + vibrationDuration;
  if(now >= vibrationEndTime) {
    ps2.vibrate(2, 0);
    vibrationStartedTime = -1;
  }
}

int WirelessController::to256Position(int rawPosition) {
  return ((rawPosition - 128) * -2);
}


WirelessController::WirelessController(int pin1, int pin2) {
  for(int i = 0; i < 26; i++) {
    buttonStates[i] = 1;
    axisStates[i] = 0;
    buttonCallbacks[i] = NULL;
    axisCallbacks[i] = NULL;
  }
  for(int i = 0; i < 26; i++) { }
  ps2 = Cytron_PS2Shield(pin1, pin2);
  ps2.begin(9600);
}

void WirelessController::poll() {
  pollButtonState(PS2_TRIANGLE);
  pollButtonState(PS2_CIRCLE);
  pollButtonState(PS2_CROSS);
  pollButtonState(PS2_SQUARE);

  pollButtonState(PS2_LEFT_1);
  pollButtonState(PS2_LEFT_2);
  pollButtonState(PS2_RIGHT_1);
  pollButtonState(PS2_RIGHT_2);

  pollButtonState(PS2_UP);
  pollButtonState(PS2_RIGHT);
  pollButtonState(PS2_DOWN);
  pollButtonState(PS2_LEFT);

  pollButtonState(PS2_START);
  pollButtonState(PS2_SELECT);

  pollButtonState(PS2_JOYSTICK_LEFT);
  pollButtonState(PS2_JOYSTICK_RIGHT);

  pollAxisState(PS2_JOYSTICK_LEFT_X_AXIS);
  pollAxisState(PS2_JOYSTICK_LEFT_Y_AXIS);
  pollAxisState(PS2_JOYSTICK_RIGHT_X_AXIS);
  pollAxisState(PS2_JOYSTICK_RIGHT_Y_AXIS);

  maybeEndVibration();
}

void WirelessController::pollButtonState(int button) {
  if(buttonCallbacks[button] == NULL) return;

  int newButtonState = ps2.readButton(button);
  bool buttonWasPressed = buttonStates[button] == 0;
  bool buttonIsReleased = newButtonState == 1;
  if(buttonWasPressed && buttonIsReleased) {
    buttonCallbacks[button]();
  }

  buttonStates[button] = newButtonState;
}

void WirelessController::pollAxisState(int axis) {
  if(axisCallbacks[axis] == NULL) return;

  int newAxisPoisition = to256Position(ps2.readButton(axis));
  int oldAxisPosition = axisStates[axis];
  if(newAxisPoisition != oldAxisPosition) {
    axisCallbacks[axis](newAxisPoisition);
  }

  axisStates[axis] = newAxisPoisition;
}

int WirelessController::getAxisState(int axis) {
  return to256Position(ps2.readButton(axis));
}

void WirelessController::onButtonPressed(int button, void (*func)()) {
  buttonCallbacks[button] = func;
}

void WirelessController::onAxisChange(int axis, void (*func)(int)) {
   axisCallbacks[axis] = func;
}

void WirelessController::vibrate(int durationMilliseconds, int intensity) {
  vibrationStartedTime = millis();
  vibrationDuration = durationMilliseconds;
  ps2.vibrate(2, intensity);
}

