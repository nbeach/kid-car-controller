#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class Logger {
    public:
    Logger(int baud) {
        Serial.begin(baud);
    }
    void info(String text) {
        Serial.println(text);
    }

};

#endif