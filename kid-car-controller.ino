#include "Arduino.h"
#include <SoftwareSerial.h>
#include "src/control/Controller.h"
#include "src/control/ManualThrottle.h"
#include "src/motor/AbstractMotor.h"
#include "src/motor/NullMotor.h"
#include "src/motor/CompositeMotor.h"
#include "src/motor/RampingSpeedLimitedEmergencyStopMotor.h"
#include "src/motor/Motor.h"
#include "src/selection/RampingSelector.h"
#include "src/selection/SpeedLimitSelector.h"

const int DISABLE_DRIVE_MOTORS = false;
int DISABLE_MANUAL_THROTTLE = false;

Controller controller;
ManualThrottle* manualThrottle;
AbstractMotor* steeringMotor;
RampingSpeedLimitedEmergencyStopMotor* driveMotor;
RampingSelector driveMotorRampingSelector;
SpeedLimitSelector driveMotorSpeedLimitSelector;
int lastControllerThrottlePosition = 0;

void setup()
{
  Serial.begin(115200);

  controller = Controller();
  manualThrottle = new ManualThrottle(0, 1, 2);
  steeringMotor = new Motor(11, 13);
  AbstractMotor* baseMotor = DISABLE_DRIVE_MOTORS ? (AbstractMotor*)new NullMotor() : (AbstractMotor*)new CompositeMotor();
  driveMotor = new RampingSpeedLimitedEmergencyStopMotor(baseMotor);

  driveMotorRampingSelector = RampingSelector();
  driveMotor->setRampingRate(driveMotorRampingSelector.currentRate());

  driveMotorSpeedLimitSelector = SpeedLimitSelector();
  driveMotor->setSpeedLimit(driveMotorSpeedLimitSelector.currentLimit());

  manualThrottle->onChange([](int position){ 
      if(DISABLE_MANUAL_THROTTLE) return;
      Serial.println("Manual Throttle Position: " + String(position));
      if(lastControllerThrottlePosition != 0) {
        Serial.println("Controller Throttle Engaged. Ignoring Manual Throttle Input.");
        return;
      }
      driveMotor->setSpeed(position);
  });

  controller.onAxisChange(PS2_JOYSTICK_RIGHT_Y_AXIS, [](int position){ 
      Serial.println("Controller Throttle Position: " + String(position));
      lastControllerThrottlePosition = position;
      if(!DISABLE_MANUAL_THROTTLE && position == 0) {
         driveMotor->setSpeed(manualThrottle->getPosition());
      } else {
         driveMotor->setSpeed(position);
      }  
  });

  controller.onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){ 
      Serial.println("Steering Position: " + String(position));
      steeringMotor->setSpeed(position);
  });

  controller.onButtonPressed(PS2_LEFT_1, [](){ 
    int oldLimit = driveMotorSpeedLimitSelector.currentLimit();
    int newLimit = driveMotorSpeedLimitSelector.decrease();
    if(newLimit != oldLimit) controller.vibrate(150, 128);
    driveMotor->setSpeedLimit(newLimit);
  });

  controller.onButtonPressed(PS2_RIGHT_1, [](){ 
    int oldLimit = driveMotorSpeedLimitSelector.currentLimit();
    int newLimit = driveMotorSpeedLimitSelector.increase();
    if(newLimit != oldLimit) controller.vibrate(150, 128);
    driveMotor->setSpeedLimit(newLimit);
  });

  controller.onButtonPressed(PS2_LEFT_2, [](){ 
    double oldRate = driveMotorRampingSelector.currentRate();
    double newRate = driveMotorRampingSelector.decrease();
    if(newRate != oldRate) controller.vibrate(150, 128);
    driveMotor->setRampingRate(newRate);
  });

  controller.onButtonPressed(PS2_RIGHT_2, [](){ 
    double oldRate = driveMotorRampingSelector.currentRate();
    double newRate = driveMotorRampingSelector.increase();
    if(newRate != oldRate) controller.vibrate(150, 128);
    driveMotor->setRampingRate(newRate);
  });

  controller.onButtonPressed(PS2_TRIANGLE, [](){ 
    driveMotor->toggleEmergencyStop();
    controller.vibrate(200, 128);
  });

  controller.onButtonPressed(PS2_SQUARE, [](){ 
    DISABLE_MANUAL_THROTTLE = !DISABLE_MANUAL_THROTTLE;
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


