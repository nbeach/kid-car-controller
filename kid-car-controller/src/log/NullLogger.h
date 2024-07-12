#ifndef NullLogger_h
#define NullLogger_h

#include "WString.h"
#include "AbstractLogger.h"

class NullLogger : public AbstractLogger {
    public:
        void info(String message) { }
};

#endif