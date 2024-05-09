#include "Cytron_PS2Shield.h"

class Controller {
  Cytron_PS2Shield ps2;

  protected:
  int to256Position(int rawPosition) {
    return ((rawPosition - 128) * -2);
  }

  public:
  Controller() {
     Cytron_PS2Shield ps2 = Cytron_PS2Shield(8,9);
     ps2.begin(9600);
  }

  int throttlePosition() {
      int rawPosition = ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);
      return to256Position(rawPosition);
  }

  int steeringPosition() {
      int rawPosition = ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS);
      return to256Position(rawPosition);
  }
};