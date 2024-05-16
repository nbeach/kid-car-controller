#include "Arduino.h"
#include <SoftwareSerial.h>
#include "src/control/WirelessController.h"
#include "src/control/ThrottlePedal.h"
#include "src/control/PriorityCompositeThrottle.h"
#include "src/control/WirelessControllerThrottle.h"
#include "src/motor/NullMotor.h"
#include "src/motor/Motor.h"
#include "src/motor/DriveMotor.h"
#include "src/motor/CompositeMotor.h"
#include "src/selection/SettingSelector.h"

const int DISABLE_DRIVE_MOTORS = false;

const int SPEED_LIMIT_COUNT = 5;
const int SPEED_LIMITS = new int[SPEED_LIMIT_COUNT] { 64, 88, 112, 184, 256 };
const int SPEED_LIMITS_DEFAULT_INDEX = 2;

const int ACCELERATION_RAMPING_RATE_COUNT = 5;
const int ACCELERATION_RAMPING_RATES = new double[ACCELERATION_RAMPING_RATE_COUNT] { 0.051, 0.088, 0.16, 0.36, 1.6 };
const int ACCELERATION_RAMPING_RATE_DEFAULT_INDEX = 2;

const int STEERING_MOTOR_PIN_1 = 11;
const int STEERING_MOTOR_PIN_2 = 13;

const int CONTROLLER_PIN_1 = 8;
const int CONTROLLER_PIN_2 = 9;
const int CONTROLLER_BAUD = 9600;

const int THROTTLE_PEDAL_ACCELERATOR_ANALOG_PIN = A0;
const int THROTTLE_PEDAL_FORWARD_ANALOG_PIN = A1;
const int THROTTLE_PEDAL_REVERSE_ANALOG_PIN = A2;

const int DRIVE_MOTOR_COUNT = 4;
const int REAR_LEFT_MOTOR_PIN_1 = 3;
const int REAR_LEFT_MOTOR_PIN_2 = 2;
const int REAR_RIGHT_MOTOR_PIN_1 = 6;
const int REAR_RIGHT_MOTOR_PIN_2 = 7;
const int FRONT_LEFT_MOTOR_PIN_1 = 5;
const int FRONT_LEFT_MOTOR_PIN_2 = 4;
const int FRONT_RIGHT_MOTOR_PIN_1 = 10;
const int FRONT_RIGHT_MOTOR_PIN_2 = 12;

WirelessController* controller;
PriorityCompositeThrottle* throttle;

SettingSelector<int>* speedLimitSelector;
SettingSelector<double>* accelerationRampingSelector;

Motor* steeringMotor;
DriveMotor* driveMotor;

void setup() {
  Serial.begin(115200);
  
  // Wirless Controller
  controller = new WirelessController(CONTROLLER_PIN_1, CONTROLLER_PIN_2, CONTROLLER_BAUD);

  //Drive Motor
  AbstractMotor** motors = new AbstractMotor*[DRIVE_MOTOR_COUNT] {
    new Motor(REAR_LEFT_MOTOR_PIN_1, REAR_LEFT_MOTOR_PIN_2),
    new Motor(REAR_RIGHT_MOTOR_PIN_1, REAR_RIGHT_MOTOR_PIN_2),
    new Motor(FRONT_LEFT_MOTOR_PIN_1, FRONT_LEFT_MOTOR_PIN_2),
    new Motor(FRONT_RIGHT_MOTOR_PIN_1, FRONT_RIGHT_MOTOR_PIN_2)
  };

  AbstractMotor* baseMotor = DISABLE_DRIVE_MOTORS
    ? (AbstractMotor*)new NullMotor()
    : (AbstractMotor*)new CompositeMotor(motors, DRIVE_MOTOR_COUNT);

  driveMotor = new DriveMotor(baseMotor);

  //Steering Motor
  steeringMotor = new Motor(STEERING_MOTOR_PIN_1, STEERING_MOTOR_PIN_2);

  controller->onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){
    Serial.println("Steering Position: " + String(position));
    steeringMotor->setSpeed(position);
  });

  //Throttle
  WirelessControllerThrottle* controllerThrottle = new WirelessControllerThrottle(controller, PS2_JOYSTICK_RIGHT_Y_AXIS);
  ThrottlePedal* pedal = new ThrottlePedal(
    THROTTLE_PEDAL_ACCELERATOR_ANALOG_PIN,
    THROTTLE_PEDAL_FORWARD_ANALOG_PIN,
    THROTTLE_PEDAL_REVERSE_ANALOG_PIN
  );

  throttle = new PriorityCompositeThrottle(controllerThrottle, pedal);

  throttle->onPositionChange([](int position){
    Serial.println("Throttle Position: " + String(position));
    driveMotor->setSpeed(position);
  });

  //Speed Limit Selector
  speedLimitSelector = new SettingSelector<int>(SPEED_LIMITS, SPEED_LIMIT_COUNT, SPEED_LIMITS_DEFAULT_INDEX);
  driveMotor->setSpeedLimit(speedLimitSelector->currentSetting());

  speedLimitSelector->onChange([](int speed){
    Serial.println("Speed Limit: " + String(speed));
    driveMotor->setSpeedLimit(speed);
  });

  controller->onButtonPressed(PS2_LEFT_1, [](){
    bool changed = speedLimitSelector->decrease();
    controller->vibrate(changed ? VIBRATION_LIGHT : VIBRATION_HEAVY);
  });

  controller->onButtonPressed(PS2_RIGHT_1, [](){
    bool changed = speedLimitSelector->increase();
    controller->vibrate(changed ? VIBRATION_LIGHT : VIBRATION_HEAVY);
  });

  //Acceleration Ramp Rate Selector
  accelerationRampingSelector = new SettingSelector<double>(
    ACCELERATION_RAMPING_RATES,
    ACCELERATION_RAMPING_RATE_COUNT,
    ACCELERATION_RAMPING_RATE_DEFAULT_INDEX
  );
  driveMotor->setAccelerationRamping(accelerationRampingSelector->currentSetting());

  accelerationRampingSelector->onChange([](double rate){
    Serial.println("Acceleration Ramping: " + String(rate));
    driveMotor->setAccelerationRamping(rate);
  });

  controller->onButtonPressed(PS2_LEFT_2, [](){ 
    bool changed = accelerationRampingSelector->decrease();
    controller->vibrate(changed ? VIBRATION_LIGHT : VIBRATION_HEAVY);
  });

  controller->onButtonPressed(PS2_RIGHT_2, [](){ 
    bool changed = accelerationRampingSelector->increase();
    controller->vibrate(changed ? VIBRATION_LIGHT : VIBRATION_HEAVY);
  });

  //Emergency Stop
  controller->onButtonPressed(PS2_TRIANGLE, [](){
    bool stopped = driveMotor->toggleEmergencyStop();
    Serial.println("Emergency Stop Enabled: " + String(stopped));
    controller->vibrate(stopped ? VIBRATION_HEAVY : VIBRATION_LIGHT);
  });

  //Secondary Throttle Disable
  controller->onButtonPressed(PS2_SQUARE, [](){ 
    bool disabled = throttle->toggleDisableSecondary();
    Serial.println("Throttle Pedal Disabled: " + String(disabled));
    controller->vibrate(disabled ? VIBRATION_HEAVY : VIBRATION_LIGHT);
  });

  Serial.println("Init Complete");
}

void loop() {
  controller->poll();
  throttle->poll();
  driveMotor->tick();
}


