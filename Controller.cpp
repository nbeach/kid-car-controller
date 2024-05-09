#include "Cytron_PS2Shield.h"

typedef void(*buttonCallback)();
typedef void(*axisCallback)(int);

class Controller {
  protected:
  Cytron_PS2Shield ps2;
  int buttonStates[26];
  int axisStates[26];
  buttonCallback buttonCallbacks[26];
  axisCallback axisCallbacks[26];

  public:
  Controller() {
    for(int i = 0; i < 26; i++) {
      buttonStates[i] = 1;
      axisStates[i] = 0;
      buttonCallbacks[i] = NULL;
      axisCallbacks[i] = NULL;
    }
    for(int i = 0; i < 26; i++) { }
    ps2 = Cytron_PS2Shield(8,9);
    ps2.begin(9600);
  }

  void poll() {
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
  }

  void pollButtonState(int button) {
    if(buttonCallbacks[button] == NULL) return;

    int newButtonState = ps2.readButton(button);
    bool buttonWasPressed = buttonStates[button] == 0;
    bool buttonIsReleased = newButtonState == 1;
    if(buttonWasPressed && buttonIsReleased) {
      buttonCallbacks[button]();
    }

    buttonStates[button] = newButtonState;
  }

  void pollAxisState(int axis) {
    if(axisCallbacks[axis] == NULL) return;

    int newAxisPoisition = ps2.readButton(axis);
    int oldAxisPosition = axisStates[axis];
    if(newAxisPoisition != oldAxisPosition) {
      axisCallbacks[axis](newAxisPoisition);
    }

    axisStates[axis] = newAxisPoisition;
  }

  void onButtonPressed(int button, void (*func)()) {
    buttonCallbacks[button] = func;
  }

  void onAxisChange(int axis, void (*func)(int)) {
     axisCallbacks[axis] = func;
  }
};