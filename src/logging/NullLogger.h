#ifndef NullLogger_h
#define NullLogger_h

#include <Arduino.h>
#include "./AbstractLogger.h"

class NullLogger : public AbstractLogger {
    public:
        void error(String text) {}
        void info(String text) {}
        void debug(String text) {}
        void trace(String text) {}
        void setLogLevel(LogLevel level) {}
};

#endif