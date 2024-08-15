#ifndef SerialLogger_h
#define SerialLogger_h

#include "./AbstractLogger.h"
#include <Arduino.h>

class SerialLogger : public AbstractLogger {
public:
  using AbstractLogger::AbstractLogger;

  void _error(String text) override { Serial.println("ERROR: " + text); }
  void _info(String text) override { Serial.println("INFO: " + text); }
  void _debug(String text) override { Serial.println("DEBUG: " + text); }
  void _trace(String text) override { Serial.println("TRACE: " + text); }
};

#endif