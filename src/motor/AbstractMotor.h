#ifndef AbstractMotor_h
#define AbstractMotor_h

class AbstractMotor {
public:
  virtual void setSpeed(int speed);
  virtual ~AbstractMotor() = default;
};

#endif