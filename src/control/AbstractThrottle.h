#ifndef AbstractThrottle_h
#define AbstractThrottle_h

class AbstractThrottle {
public:
  virtual int getPosition();
  virtual ~AbstractThrottle() = default;
};

#endif