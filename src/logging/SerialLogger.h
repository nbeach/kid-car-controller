#ifndef SerialLogger_h
#define SerialLogger_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "./AbstractLogger.h"

class SerialLogger : public AbstractLogger {
    private:
        LogLevel logLevel;
    public:
        SerialLogger(LogLevel logLevel) {
            this->logLevel = logLevel;
        }
        
        void error(String text) {
            if(logLevel >= LogLevel::ERROR) Serial.println("ERROR: " + text);
        }

        void info(String text) {
            if(logLevel >= LogLevel::INFO) Serial.println("INFO: " + text);
        }

        void debug(String text) {
            if(logLevel >= LogLevel::DEBUG) Serial.println("DEBUG: " + text);
        }

        void trace(String text) {
            if(logLevel >= LogLevel::TRACE) Serial.println("TRACE: " + text);
        }

        void setLogLevel(LogLevel level) {
            this->logLevel = logLevel;
        }
};

#endif