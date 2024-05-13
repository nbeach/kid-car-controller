#include "Arduino.h"
#include <SoftwareSerial.h>
#include "src/control/WirelessController.h"
#include "src/control/ThrottlePedal.h"
#include "src/control/PriorityCompositeThrottle.h"
#include "src/control/WirelessControllerThrottle.h"
#include "src/motor/NullMotor.h"
#include "src/motor/CompositeMotor.h"
#include "src/motor/RampingSpeedLimitedEmergencyStopMotor.h"
#include "src/motor/Motor.h"
#include "src/selection/RampingSelector.h"
#include "src/selection/SpeedLimitSelector.h"

const int DISABLE_DRIVE_MOTORS = false;

WirelessController* controller;
PriorityCompositeThrottle* throttle;

Motor* steeringMotor;
RampingSpeedLimitedEmergencyStopMotor* driveMotor;

void setup() {
  Serial.begin(115200);

  // Wirless Controller
  controller = new WirelessController(8, 9);

  //Throttle
  WirelessControllerThrottle* controllerThrottle = new WirelessControllerThrottle(controller, PS2_JOYSTICK_RIGHT_Y_AXIS);
  ThrottlePedal* pedal = new ThrottlePedal(0, 1, 2);
  throttle = new PriorityCompositeThrottle(controllerThrottle, pedal);

  //Steering Motor
  steeringMotor = new Motor(11, 13);

  //Drive Motor
  AbstractMotor* baseMotor = DISABLE_DRIVE_MOTORS ? (AbstractMotor*)new NullMotor() : (AbstractMotor*)new CompositeMotor();
  driveMotor = new RampingSpeedLimitedEmergencyStopMotor(baseMotor);

  throttle->onPositionChange([](int position){
      Serial.println("Throttle Position: " + String(position));
      driveMotor->setSpeed(position);
  });

  controller->onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){ 
      Serial.println("Steering Position: " + String(position));
      steeringMotor->setSpeed(position);
  });

  controller->onButtonPressed(PS2_LEFT_1, [](){ 
    Serial.println("Speed Limit Decreased");
    controller->vibrate(100, 128);
  });

  controller->onButtonPressed(PS2_RIGHT_1, [](){ 
    Serial.println("Speed Limit Increased");
    controller->vibrate(100, 128);
  });

  controller->onButtonPressed(PS2_LEFT_2, [](){ 
    Serial.println("Acceleration Ramp Rate Decreased");
    controller->vibrate(100, 128);
  });

  controller->onButtonPressed(PS2_RIGHT_2, [](){ 
    Serial.println("Acceleration Ramp Rate Increased");
    controller->vibrate(100, 128);
  });

  controller->onButtonPressed(PS2_TRIANGLE, [](){ 
    Serial.println("Emergency Stop Toggled");
    driveMotor->toggleEmergencyStop();
    controller->vibrate(200, 128);
  });

  controller->onButtonPressed(PS2_SQUARE, [](){ 
    throttle->toggleDisableSecondary();
    controller->vibrate(200, 128);
  });

  delay(200);
  Serial.println("Init Complete");
}

void loop() {
  controller->poll();
  throttle->poll();
  driveMotor->tick();
}


