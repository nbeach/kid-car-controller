#ifndef AbstractLogger_h
#define AbstractLogger_h

#ifdef ARDUINO
#include <WString.h>
#else
#include "../../lib/WString.h"
#endif

enum LogLevel { ERROR = 0, INFO = 1, DEBUG = 2, TRACE = 3 };

class AbstractLogger {
protected:
  LogLevel logLevel;

  virtual void _error(String text);
  virtual void _info(String text);
  virtual void _debug(String text);
  virtual void _trace(String text);

  bool shouldLog(LogLevel levelOfLogMessage) { return logLevel >= levelOfLogMessage; }

public:
  explicit AbstractLogger(LogLevel logLevel) { this->logLevel = logLevel; }
  virtual ~AbstractLogger() = default;

  void setLogLevel(LogLevel logLevel) { this->logLevel = logLevel; }

  LogLevel getLogLevel() const { return this->logLevel; }

  String getLogLevelName() const {
    if (logLevel == ERROR)
      return "ERROR";
    if (logLevel == INFO)
      return "INFO";
    if (logLevel == DEBUG)
      return "DEBUG";
    if (logLevel == TRACE)
      return "TRACE";
    return "UNKNOWN";
  }

  void error(String text) {
    if (shouldLog(ERROR))
      _error(text);
  };
  void info(String text) {
    if (shouldLog(INFO))
      _info(text);
  };
  void debug(String text) {
    if (shouldLog(DEBUG))
      _debug(text);
  };
  void trace(String text) {
    if (shouldLog(TRACE))
      _trace(text);
  };
};

#endif