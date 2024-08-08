#ifndef NullLogger_h
#define NullLogger_h

#include <Arduino.h>
#include "./AbstractLogger.h"

class NullLogger : public AbstractLogger {
    public:
        void info(String text) {}
};

#endif