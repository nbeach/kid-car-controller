#include "Arduino.h"
#include <SoftwareSerial.h>
#include "src/control/WirelessController.h"
#include "src/control/ThrottlePedal.h"
#include "src/control/PriorityCompositeThrottle.h"
#include "src/control/WirelessControllerThrottle.h"
#include "src/motor/NullMotor.h"
#include "src/motor/Motor.h"
#include "src/motor/SteeringMotor.h"
#include "src/motor/DriveMotor.h"
#include "src/motor/CompositeMotor.h"
#include "src/selection/SettingSelector.h"

const int DISABLE_DRIVE_MOTORS = false;

const int SPEED_LIMIT_COUNT = 11;
int* SPEED_LIMITS = new int[SPEED_LIMIT_COUNT] { 16, 32, 48, 64, 80, 96, 112, 128, 160, 192, 256 };
const int SPEED_LIMITS_DEFAULT_INDEX = 2;

const int STEERING_MOTOR_PIN_1 = 5;
const int STEERING_MOTOR_PIN_2 = 13;
const int STEERING_MOTOR_RELAY_PIN = A3;

const int CONTROLLER_PIN_1 = 0;
const int CONTROLLER_PIN_2 = 1;
const int CONTROLLER_BAUD = 9600;

const int THROTTLE_PEDAL_ACCELERATOR_ANALOG_PIN = A0;
const int THROTTLE_PEDAL_FORWARD_ANALOG_PIN = A4;
const int THROTTLE_PEDAL_REVERSE_ANALOG_PIN = A2;

const int DRIVE_MOTOR_COUNT = 4;
const int REAR_LEFT_MOTOR_PIN_1 = 9;
const int REAR_LEFT_MOTOR_PIN_2 = 2;
const int REAR_RIGHT_MOTOR_PIN_1 = 10;
const int REAR_RIGHT_MOTOR_PIN_2 = 7;
const int FRONT_LEFT_MOTOR_PIN_1 = 3;
const int FRONT_LEFT_MOTOR_PIN_2 = 4;
const int FRONT_RIGHT_MOTOR_PIN_1 = 11;
const int FRONT_RIGHT_MOTOR_PIN_2 = 12;

WirelessController* controller;
PriorityCompositeThrottle* throttle;

SettingSelector<int>* speedLimitSelector;

SteeringMotor* steeringMotor;
DriveMotor* driveMotor;

void setup() {
  Serial.begin(115200);

  //Set PWM frequency to 3921.16Hz
  TCCR1B = TCCR1B & B11111000 | B00000010;  //Pins 9 and 10
  TCCR2B = TCCR2B & B11111000 | B00000010;  //Pins 3 and 11


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
  steeringMotor = new SteeringMotor(new Motor(STEERING_MOTOR_PIN_1, STEERING_MOTOR_PIN_2), STEERING_MOTOR_RELAY_PIN);

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


