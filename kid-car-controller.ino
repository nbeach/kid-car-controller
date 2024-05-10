#include <SoftwareSerial.h>
#include "Controller.cpp"
#include "Motor.cpp"
#include "RampingSelector.cpp"
#include "SpeedLimitSelector.cpp"

const int DISABLE_DRIVE_MOTORS = false;

Controller controller;
AbstractMotor* steeringMotor;
RampingSpeedLimitedEmergencyStopMotor* driveMotor;
RampingSelector* driveMotorRampingSelector;
SpeedLimitSelector* driveMotorSpeedLimitSelector;

int to256Position(int rawPosition) {
  return ((rawPosition - 128) * -2);
}

void setup()
{
  Serial.begin(9600);

  controller = Controller();
  steeringMotor = new Motor(11, 13);
  AbstractMotor* baseMotor = DISABLE_DRIVE_MOTORS ? (AbstractMotor*)new NullMotor() : (AbstractMotor*)new CompositeMotor();
  driveMotor = new RampingSpeedLimitedEmergencyStopMotor(baseMotor);

  driveMotorRampingSelector = new RampingSelector();
  driveMotor->setMaxSpeedStepsPerMillisecond(driveMotorRampingSelector->currentRate());

  driveMotorSpeedLimitSelector = new SpeedLimitSelector();
  driveMotor->setSpeedLimit(driveMotorSpeedLimitSelector->currentLimit());

  controller.onAxisChange(PS2_JOYSTICK_RIGHT_Y_AXIS, [](int position){ 
      Serial.println("Throttle Position: " + String(to256Position(position)));
      driveMotor->setSpeed(to256Position(position));
  });

  controller.onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){ 
      Serial.println("Steering Position: " + String(to256Position(position)));
      steeringMotor->setSpeed(to256Position(position));
  });

  controller.onButtonPressed(PS2_LEFT_1, [](){ 
    int limit = driveMotorSpeedLimitSelector->decrease();
    driveMotor->setSpeedLimit(limit);
  });

  controller.onButtonPressed(PS2_RIGHT_1, [](){ 
    int limit = driveMotorSpeedLimitSelector->increase();
    driveMotor->setSpeedLimit(limit);
  });

  controller.onButtonPressed(PS2_LEFT_2, [](){ 
    double rate = driveMotorRampingSelector->decrease();
    driveMotor->setMaxSpeedStepsPerMillisecond(rate);
  });

  controller.onButtonPressed(PS2_RIGHT_2, [](){ 
    double rate = driveMotorRampingSelector->increase();
    driveMotor->setMaxSpeedStepsPerMillisecond(rate);
  });

  controller.onButtonPressed(PS2_TRIANGLE, [](){ 
    driveMotor->toggleEmergencyStop();
  });

  delay(1000);
}

void loop()
{
  controller.poll();
  driveMotor->tick();
}


