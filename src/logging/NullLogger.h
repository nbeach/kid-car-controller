#ifndef NullLogger_h
#define NullLogger_h

#include "./AbstractLogger.h"

class NullLogger : public AbstractLogger {
public:
  using AbstractLogger::AbstractLogger;

  void _error(String text) override {}
  void _info(String text) override {}
  void _debug(String text) override {}
  void _trace(String text) override {}
};

#endif