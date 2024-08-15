// #include <gtest/gtest.h>
// #include "../.././src/motor/CompositeMotor.h"
// #include "../../../src/motor/NullMotor.h"
// #include "../../../src/logging/NullLogger.h"
//
// TEST(CompositeMotorTest, CommandsAllMotorsToTheSameSpeed) {
//     auto* logger = new NullLogger(LogLevel::INFO);
//     auto count = 2;
//     auto* motor1 = new NullMotor(logger);
//     auto* motor2 = new NullMotor(logger);
//     auto** motors = new AbstractMotor*[count] { motor1, motor2 };
//
//     auto subject = CompositeMotor(motors, count, logger);
//
//     subject.setSpeed(100);
//
//     EXPECT_EQ(motor1->getSpeed(), 100);
//     EXPECT_EQ(motor2->getSpeed(), 100);
// }