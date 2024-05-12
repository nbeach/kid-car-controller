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

// RampingSelector driveMotorRampingSelector;
// SpeedLimitSelector driveMotorSpeedLimitSelector;

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

  // driveMotorRampingSelector = RampingSelector();
  // driveMotor->setRampingRate(driveMotorRampingSelector.currentRate());

  // driveMotorSpeedLimitSelector = SpeedLimitSelector();
  // driveMotor->setSpeedLimit(driveMotorSpeedLimitSelector.currentLimit());

  throttle->onPositionChange([](int position){
      Serial.println("Throttle Position: " + String(position));
      driveMotor->setSpeed(position);
  });

  controller->onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){ 
      Serial.println("Steering Position: " + String(position));
      steeringMotor->setSpeed(position);
  });

  // controller->onButtonPressed(PS2_LEFT_1, [](){ 
  //   int oldLimit = driveMotorSpeedLimitSelector.currentLimit();
  //   int newLimit = driveMotorSpeedLimitSelector.decrease();
  //   if(newLimit != oldLimit) controller->vibrate(150, 128);
  //   driveMotor->setSpeedLimit(newLimit);
  // });

  // controller->onButtonPressed(PS2_RIGHT_1, [](){ 
  //   int oldLimit = driveMotorSpeedLimitSelector.currentLimit();
  //   int newLimit = driveMotorSpeedLimitSelector.increase();
  //   if(newLimit != oldLimit) controller->vibrate(150, 128);
  //   driveMotor->setSpeedLimit(newLimit);
  // });

  // controller->onButtonPressed(PS2_LEFT_2, [](){ 
  //   double oldRate = driveMotorRampingSelector.currentRate();
  //   double newRate = driveMotorRampingSelector.decrease();
  //   if(newRate != oldRate) controller->vibrate(150, 128);
  //   driveMotor->setRampingRate(newRate);
  // });

  // controller->onButtonPressed(PS2_RIGHT_2, [](){ 
  //   double oldRate = driveMotorRampingSelector.currentRate();
  //   double newRate = driveMotorRampingSelector.increase();
  //   if(newRate != oldRate) controller->vibrate(150, 128);
  //   driveMotor->setRampingRate(newRate);
  // });

  controller->onButtonPressed(PS2_TRIANGLE, [](){ 
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


