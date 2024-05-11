#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Controller.cpp"
#include "ManualThrottle.cpp"
#include "Motor.cpp"
#include "RampingSelector.cpp"
#include "SpeedLimitSelector.cpp"

const int DISABLE_DRIVE_MOTORS = false;

Controller controller;
ManualThrottle* manualThrottle;
AbstractMotor* steeringMotor;
RampingSpeedLimitedEmergencyStopMotor* driveMotor;
RampingSelector* driveMotorRampingSelector;
SpeedLimitSelector* driveMotorSpeedLimitSelector;

void setup()
{
  Serial.begin(9600);

  controller = Controller();
  manualThrottle = new ManualThrottle(0, 1, 2);
  steeringMotor = new Motor(11, 13);
  AbstractMotor* baseMotor = DISABLE_DRIVE_MOTORS ? (AbstractMotor*)new NullMotor() : (AbstractMotor*)new CompositeMotor();
  driveMotor = new RampingSpeedLimitedEmergencyStopMotor(baseMotor);

  driveMotorRampingSelector = new RampingSelector();
  driveMotor->setMaxSpeedStepsPerMillisecond(driveMotorRampingSelector->currentRate());

  driveMotorSpeedLimitSelector = new SpeedLimitSelector();
  driveMotor->setSpeedLimit(driveMotorSpeedLimitSelector->currentLimit());

  manualThrottle->onChange([](int position){ 
      Serial.println("Manual Throttle Position: " + String(position));
  });

  controller.onAxisChange(PS2_JOYSTICK_RIGHT_Y_AXIS, [](int position){ 
      Serial.println("Controller Throttle Position: " + String(position));
      driveMotor->setSpeed(position);
  });

  controller.onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){ 
      Serial.println("Steering Position: " + String(position));
      steeringMotor->setSpeed(position);
  });

  controller.onButtonPressed(PS2_LEFT_1, [](){ 
    int oldLimit = driveMotorSpeedLimitSelector->currentLimit();
    int newLimit = driveMotorSpeedLimitSelector->decrease();
    if(newLimit != oldLimit) controller.vibrate(150, 128);
    driveMotor->setSpeedLimit(newLimit);
  });

  controller.onButtonPressed(PS2_RIGHT_1, [](){ 
    int oldLimit = driveMotorSpeedLimitSelector->currentLimit();
    int newLimit = driveMotorSpeedLimitSelector->increase();
    if(newLimit != oldLimit) controller.vibrate(150, 128);
    driveMotor->setSpeedLimit(newLimit);
  });

  controller.onButtonPressed(PS2_LEFT_2, [](){ 
    double oldRate =  driveMotorRampingSelector->currentRate();
    double newRate = driveMotorRampingSelector->decrease();
    if(newRate != oldRate) controller.vibrate(150, 128);
    driveMotor->setMaxSpeedStepsPerMillisecond(newRate);
  });

  controller.onButtonPressed(PS2_RIGHT_2, [](){ 
    double oldRate =  driveMotorRampingSelector->currentRate();
    double newRate = driveMotorRampingSelector->increase();
    if(newRate != oldRate) controller.vibrate(150, 128);
    driveMotor->setMaxSpeedStepsPerMillisecond(newRate);
  });

  controller.onButtonPressed(PS2_TRIANGLE, [](){ 
    driveMotor->toggleEmergencyStop();
    controller.vibrate(200, 128);
  });

  delay(200);
}

void loop()
{
  controller.poll();
  manualThrottle->poll();
  driveMotor->tick();
}


