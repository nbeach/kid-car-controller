#include <SoftwareSerial.h>
#include "Logger.cpp"
#include "Controller.cpp"
#include "Steering.cpp"
#include "Drivetrain.cpp"

Logger logger;
Controller controller;
Steering steering;
Drivetrain drivetrain;


void setup()
{
  Serial.begin(9600);
  logger = Logger();
  controller = Controller();
  steering = Steering();
  drivetrain = Drivetrain();
  delay(1000);
}

void loop()
{
  int throttlePosition = controller.throttlePosition();
  drivetrain.setSpeed(throttlePosition);
  Serial.println("Throttle Position");
  Serial.println(throttlePosition);

  int steeringPosition = controller.steeringPosition();
  steering.moveSteering(steeringPosition);
  Serial.println("Steering Position");
  Serial.println(steeringPosition);
  
  delay(100);
}


