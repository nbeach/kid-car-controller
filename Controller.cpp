#include "Cytron_PS2Shield.h"

class Controller {
  Cytron_PS2Shield ps2;

  public:
  Controller() {
     Cytron_PS2Shield ps2 = Cytron_PS2Shield(8,9);
     ps2.begin(9600);
  }

  int throttle() {
      int input = ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);
      int speed =  (input-128) * -2;
      return speed;
  }
};