#include "Logger.h"

LoggerOutput *Logger::loggerOutput = nullptr;
LogLevel Logger::logLevel = LogLevel::eError;
uint32_t Logger::traceLevel = 0;