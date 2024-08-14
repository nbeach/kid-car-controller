#ifndef AbstractLogger_h
#define AbstractLogger_h

#include <Arduino.h>

enum LogLevel { ERROR = 0, INFO = 1, DEBUG = 2, TRACE = 3 };

class AbstractLogger {
protected:
  LogLevel logLevel;

  virtual void _error(String text);
  virtual void _info(String text);
  virtual void _debug(String text);
  virtual void _trace(String text);

  bool shouldLog(LogLevel levelOfLogMessage) {
    return logLevel >= levelOfLogMessage;
  }

public:
  AbstractLogger(LogLevel logLevel) { this->logLevel = logLevel; }

  void setLogLevel(LogLevel logLevel) { this->logLevel = logLevel; }

  LogLevel getLogLevel() { return this->logLevel; }

  String getLogLevelName() {
    if (logLevel == LogLevel::ERROR)
      return "ERROR";
    if (logLevel == LogLevel::INFO)
      return "INFO";
    if (logLevel == LogLevel::DEBUG)
      return "DEBUG";
    if (logLevel == LogLevel::TRACE)
      return "TRACE";
    return "UNKNOWN";
  }

  void error(String text) {
    if (shouldLog(LogLevel::ERROR))
      _error(text);
  };
  void info(String text) {
    if (shouldLog(LogLevel::INFO))
      _info(text);
  };
  void debug(String text) {
    if (shouldLog(LogLevel::DEBUG))
      _debug(text);
  };
  void trace(String text) {
    if (shouldLog(LogLevel::TRACE))
      _trace(text);
  };
};

#endif