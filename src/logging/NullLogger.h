#ifndef NullLogger_h
#define NullLogger_h

#include <Arduino.h>
#include "./AbstractLogger.h"

class NullLogger : public AbstractLogger {
    public:
        using AbstractLogger::AbstractLogger;

        void _error(String text) {}
        void _info(String text) {}
        void _debug(String text) {}
        void _trace(String text) {}
};

#endif