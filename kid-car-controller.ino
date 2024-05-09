#include <SoftwareSerial.h>
#include "Controller.cpp"
#include "Drivetrain.cpp"

Controller controller;
Drivetrain drivetrain;


void setup()
{
  Serial.begin(9600);
  controller = Controller();
  drivetrain = Drivetrain();
  delay(1000);
}

void loop()
{
  int throttlePosition = controller.throttlePosition();
  Serial.println(throttlePosition);
  drivetrain.setSpeed(throttlePosition);

  delay(100);
}


