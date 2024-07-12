#ifndef AbstractLogger_h
#define AbstractLogger_h

#include "WString.h"

class AbstractLogger {
    public:
        virtual void info(String message);
};

#endif