#ifndef SerialLogger_h
#define SerialLogger_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "./AbstractLogger.h"

class SerialLogger : public AbstractLogger {
    public:
        SerialLogger() {}
        
        void info(String text) {
            Serial.println(text);
        }
};

#endif