#ifndef AbstractLogger_h
#define AbstractLogger_h

#include <Arduino.h>

enum LogLevel {
    ERROR = 0,
    INFO = 1,
    DEBUG = 2,
    TRACE = 3
};

class AbstractLogger {
    protected:

    public:
        virtual void error(String text);
        virtual void info(String text);
        virtual void debug(String text);
        virtual void trace(String text);
        virtual void setLogLevel(LogLevel level);
};

#endif