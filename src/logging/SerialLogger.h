#ifndef SerialLogger_h
#define SerialLogger_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "./AbstractLogger.h"

class SerialLogger : public AbstractLogger {
    public:
        SerialLogger(int baud) {
            Serial.begin(baud);
        }
        
        void info(String text) {
            Serial.println(text);
        }
};

#endif