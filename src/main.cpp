#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include "control/WirelessController.h"
#include "control/ThrottlePedal.h"
#include "control/PriorityCompositeThrottle.h"
#include "control/WirelessControllerThrottle.h"
#include "motor/NullMotor.h"
#include "motor/Motor.h"
#include "motor/SteeringMotor.h"
#include "motor/DriveMotor.h"
#include "motor/CompositeMotor.h"
#include "selection/SettingSelector.h"
#include "logging/AbstractLogger.h"
#include "logging/SerialLogger.h"
#include "logging/NullLogger.h"

LogLevel DEFAULT_LOG_LEVEL = LogLevel::INFO;

const bool DISABLE_DRIVE_MOTORS = false;
const bool DISABLE_LOGGING = false;

const int SPEED_LIMIT_COUNT = 11;
int* SPEED_LIMITS = new int[SPEED_LIMIT_COUNT] { 16, 32, 48, 64, 80, 96, 112, 128, 160, 192, 256 };
const int SPEED_LIMITS_DEFAULT_INDEX = 2;

const uint8_t STEERING_MOTOR_PWM_PIN = 9;
const uint8_t STEERING_MOTOR_DIRECTION_PIN = 12;
const uint8_t STEERING_MOTOR_RELAY_PIN = A3;

// CONTROLLER_RESET_PIN = A1
const uint32_t CONTROLLER_BAUD = 9600;

const int THROTTLE_PEDAL_ACCELERATOR_ANALOG_PIN = A0;
const int THROTTLE_PEDAL_FORWARD_ANALOG_PIN = A4;
const int THROTTLE_PEDAL_REVERSE_ANALOG_PIN = A2;

const int DRIVE_MOTOR_PWM_FREQUENCY = 16000;
const int DRIVE_MOTOR_COUNT = 4;
const uint8_t REAR_LEFT_MOTOR_PWM_PIN = 3;
const uint8_t REAR_LEFT_MOTOR_DIRECTION_PIN = 4;
const uint8_t REAR_RIGHT_MOTOR_PWM_PIN = 11;
const uint8_t REAR_RIGHT_MOTOR_DIRECTION_PIN = 13;
const uint8_t FRONT_LEFT_MOTOR_PWM_PIN = 5;
const uint8_t FRONT_LEFT_MOTOR_DIRECTION_PIN = 8;
const uint8_t FRONT_RIGHT_MOTOR_PWM_PIN = 6;
const uint8_t FRONT_RIGHT_MOTOR_DIRECTION_PIN = 7;

WirelessController* controller;
PriorityCompositeThrottle* throttle;

SettingSelector<int>* speedLimitSelector;

SteeringMotor* steeringMotor;
DriveMotor* driveMotor;
AbstractLogger* logger;

void setup() {
  if(!DISABLE_LOGGING) Serial.begin(115200);
  logger = DISABLE_LOGGING 
    ? (AbstractLogger*)new NullLogger(DEFAULT_LOG_LEVEL)
    : (AbstractLogger*)new SerialLogger(DEFAULT_LOG_LEVEL);

  //Wireless Controller
  controller = new WirelessController(CONTROLLER_BAUD);

  //Drive Motor
  AbstractMotor* baseMotor;
  if(DISABLE_DRIVE_MOTORS) {
    baseMotor = (AbstractMotor*)new NullMotor(logger);
  } else {
    AbstractMotor** motors = new AbstractMotor*[DRIVE_MOTOR_COUNT] {
      new Motor(REAR_LEFT_MOTOR_PWM_PIN, REAR_LEFT_MOTOR_DIRECTION_PIN, DRIVE_MOTOR_PWM_FREQUENCY),
      new Motor(REAR_RIGHT_MOTOR_PWM_PIN, REAR_RIGHT_MOTOR_DIRECTION_PIN, DRIVE_MOTOR_PWM_FREQUENCY),
      new Motor(FRONT_LEFT_MOTOR_PWM_PIN, FRONT_LEFT_MOTOR_DIRECTION_PIN, DRIVE_MOTOR_PWM_FREQUENCY),
      new Motor(FRONT_RIGHT_MOTOR_PWM_PIN, FRONT_RIGHT_MOTOR_DIRECTION_PIN, DRIVE_MOTOR_PWM_FREQUENCY)
    };

    baseMotor = (AbstractMotor*)new CompositeMotor(motors, DRIVE_MOTOR_COUNT, logger);
  }
  driveMotor = new DriveMotor(baseMotor, logger);

  //Steering Motor
  steeringMotor = new SteeringMotor(STEERING_MOTOR_PWM_PIN, STEERING_MOTOR_DIRECTION_PIN, STEERING_MOTOR_RELAY_PIN);

  controller->onAxisChange(PS2_JOYSTICK_LEFT_X_AXIS, [](int position){
    logger->info("Steering Position: " + String(position));
    steeringMotor->setSpeed(position);
  });

  //Throttle
  WirelessControllerThrottle* controllerThrottle = new WirelessControllerThrottle(controller, PS2_JOYSTICK_RIGHT_Y_AXIS);
  ThrottlePedal* pedal = new ThrottlePedal(
    THROTTLE_PEDAL_ACCELERATOR_ANALOG_PIN,
    THROTTLE_PEDAL_FORWARD_ANALOG_PIN,
    THROTTLE_PEDAL_REVERSE_ANALOG_PIN,
    logger
  );

  throttle = new PriorityCompositeThrottle(controllerThrottle, pedal);

  throttle->onPositionChange([](int position){
    logger->info("Throttle Position: " + String(position));
    driveMotor->setSpeed(position);
  });

  //Speed Limit Selector
  speedLimitSelector = new SettingSelector<int>(SPEED_LIMITS, SPEED_LIMIT_COUNT, SPEED_LIMITS_DEFAULT_INDEX);
  driveMotor->setSpeedLimit(speedLimitSelector->currentSetting());

  speedLimitSelector->onChange([](int speed){
    logger->info("Speed Limit: " + String(speed));
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

  //Emergency Stop
  controller->onButtonPressed(PS2_TRIANGLE, [](){
    bool stopped = driveMotor->toggleEmergencyStop();
    logger->info("Emergency Stop Enabled: " + String(stopped));
    controller->vibrate(stopped ? VIBRATION_HEAVY : VIBRATION_LIGHT);
  });

  //Secondary Throttle Disable
  controller->onButtonPressed(PS2_SQUARE, [](){ 
    bool disabled = throttle->toggleDisableSecondary();
    logger->info("Throttle Pedal Disabled: " + String(disabled));
    controller->vibrate(disabled ? VIBRATION_HEAVY : VIBRATION_LIGHT);
  });

  //Log Level
  controller->onButtonPressed(PS2_SELECT, [](){
    logger->setLogLevel(logger->getLogLevel() == LogLevel::TRACE ? LogLevel::ERROR : static_cast<LogLevel>(logger->getLogLevel() + 1));
    logger->info("Log Level: " + logger->getLogLevelName());
  });

  logger->info("Init Complete");
}

void loop() {
  controller->poll();
  throttle->poll();
  driveMotor->tick();
}
