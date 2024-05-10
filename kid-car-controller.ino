#include <SoftwareSerial.h>
#include "Controller.cpp"
#include "Motor.cpp"

Controller controller;
AbstractMotor* steeringMotor;
AbstractMotor* driveMotor;

int to256Position(int rawPosition) {
  return ((rawPosition - 128) * -2);
}

AbstractMotor* steeringMotorFactory() {
  return new RampingMotor(0.128, new Motor(11, 13));
}

AbstractMotor* driveMotorFactory() {
  // AbstractMotor motors[] = { 
  //   Motor(5, 4), //Front Left
  //   Motor(10, 12), //Front Right
  //   Motor(3, 2), //Rear Left
  //   Motor(6, 7) //Rear Right
  // };

  // AbstractMotor* compositeMotor = new RealCompositeMotor(4, motors);
  return new RampingMotor(0.128, new CompositeMotor());
}

void setup()
{
  Serial.begin(9600);
  controller = Controller();
  steeringMotor = steeringMotorFactory();
  driveMotor = driveMotorFactory();

  controller.onAxisChange(PS2_JOYSTICK_RIGHT_Y_AXIS, [](int position){ 
      driveMotor->setSpeed(to256Position(position));
      Serial.println("Throttle Position: " + String(to256Position(position)));
  });

  controller.onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){ 
      steeringMotor->setSpeed(to256Position(position));
      Serial.println("Steering Position: " + String(to256Position(position)));
  });

  controller.onAxisChange(PS2_JOYSTICK_RIGHT_X_AXIS, [](int position){ Serial.println("Right Joystick X Position: " + String(to256Position(position))); });
  controller.onAxisChange(PS2_JOYSTICK_LEFT_Y_AXIS, [](int position){ Serial.println("Left Joystick Y Position: " + String(to256Position(position))); });

  controller.onButtonPressed(PS2_TRIANGLE, [](){ Serial.println("Triangle Pressed"); });
  controller.onButtonPressed(PS2_CIRCLE, [](){ Serial.println("Circle Pressed"); });
  controller.onButtonPressed(PS2_CROSS, [](){ Serial.println("Cross Pressed"); });
  controller.onButtonPressed(PS2_SQUARE, [](){ Serial.println("Square Pressed"); });

  controller.onButtonPressed(PS2_LEFT_1, [](){ Serial.println("L1 Pressed"); });
  controller.onButtonPressed(PS2_LEFT_2, [](){ Serial.println("L2 Pressed"); });
  controller.onButtonPressed(PS2_RIGHT_1, [](){ Serial.println("R1 Pressed"); });
  controller.onButtonPressed(PS2_RIGHT_2, [](){ Serial.println("R2 Pressed"); });

  controller.onButtonPressed(PS2_UP, [](){ Serial.println("DPad Up Pressed"); });
  controller.onButtonPressed(PS2_RIGHT, [](){ Serial.println("DPad Right Pressed"); });
  controller.onButtonPressed(PS2_DOWN, [](){ Serial.println("DPad Down Pressed"); });
  controller.onButtonPressed(PS2_LEFT, [](){ Serial.println("DPad Left Pressed"); });


  controller.onButtonPressed(PS2_START, [](){ Serial.println("Start Pressed"); });
  controller.onButtonPressed(PS2_SELECT, [](){ Serial.println("Select Pressed"); });

  controller.onButtonPressed(PS2_JOYSTICK_LEFT, [](){ Serial.println("Left Joystick Pressed"); });
  controller.onButtonPressed(PS2_JOYSTICK_RIGHT, [](){ Serial.println("Right Joystick Pressed"); });

  delay(1000);
}

void loop()
{
  controller.poll();
  driveMotor->tick();
  steeringMotor->tick();
}


