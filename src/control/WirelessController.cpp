#include "WirelessController.h"

void WirelessController::maybeEndVibration() {
  if (vibrationStartedTime == -1)
    return;
  int now = millis();
  int vibrationEndTime = vibrationStartedTime + vibrationDuration;
  if (now >= vibrationEndTime) {
    ps2.vibrate(2, 0);
    vibrationStartedTime = -1;
  }
}

int WirelessController::to256Position(int rawPosition) {
  return ((rawPosition - 128) * -2);
}

WirelessController::WirelessController(uint32_t baud) {
  for (int i = 0; i < 26; i++) {
    buttonStates[i] = 1;
    axisStates[i] = 0;
    buttonCallbacks[i] = nullptr;
    axisCallbacks[i] = nullptr;
  }

  ps2 = PS2Shield();
  ps2.begin(baud);
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
  if (buttonCallbacks[button] == nullptr)
    return;

  int newButtonState = ps2.readButton(button);
  bool buttonWasPressed = buttonStates[button] == 0;
  bool buttonIsReleased = newButtonState == 1;
  if (buttonWasPressed && buttonIsReleased) {
    buttonCallbacks[button]();
  }

  buttonStates[button] = newButtonState;
}

void WirelessController::pollAxisState(int axis) {
  if (axisCallbacks[axis] == nullptr)
    return;

  int newAxisPoisition = to256Position(ps2.readButton(axis));
  int oldAxisPosition = axisStates[axis];
  if (newAxisPoisition != oldAxisPosition) {
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

void WirelessController::vibrate(int level) {
  vibrationStartedTime = millis();
  vibrationDuration = level == VIBRATION_HEAVY ? 250 : 175;

  ps2.vibrate(2, level == VIBRATION_HEAVY ? 200 : 100);
}
