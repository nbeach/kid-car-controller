#ifndef SerialLogger_h
#define SerialLogger_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "./AbstractLogger.h"

class SerialLogger : public AbstractLogger {
    public:
        using AbstractLogger::AbstractLogger;

        void _error(String text) {
            Serial.println("ERROR: " + text);
        }

        void _info(String text) {
            Serial.println("INFO: " + text);
        }

        void _debug(String text) {
            Serial.println("DEBUG: " + text);
        }

        void _trace(String text) {
            Serial.println("TRACE: " + text);
        }
};

#endif