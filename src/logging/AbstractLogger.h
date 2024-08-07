#ifndef AbstractLogger_h
#define AbstractLogger_h

#include "Arduino.h"

class AbstractLogger {
    public:
    virtual void info(String text);
};

#endif