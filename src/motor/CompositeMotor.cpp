#include "CompositeMotor.h"

#include "Arduino.h"

void CompositeMotor::setSpeed(int speed) {
    Serial.println("Commanded Speed: " + String(speed));
    frontLeftMotor.setSpeed(speed);
    frontRightMotor.setSpeed(speed);
    rearLeftMotor.setSpeed(speed);
    rearRightMotor.setSpeed(speed);
}


// class RealCompositeMotor : public AbstractMotor {
//   private:
//   int count;
//   AbstractMotor* motors;

//   public:
//   RealCompositeMotor(int count, AbstractMotor* motors) {
//     this->count = count;
//     this->motors = motors;
//   }

//   void setSpeed(int speed) {
//     for (int i = 0; i < count; i++) {
//       motors[i].setSpeed(speed);
//     }
//   }
// };