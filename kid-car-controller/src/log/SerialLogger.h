#ifndef SerialLogger_h
#define SerialLogger_h

#include "WString.h"
#include "AbstractLogger.h"

class SerialLogger : public AbstractLogger {
    public:
        void info(String message) {
            Serial.println(message);
        }
};

#endif