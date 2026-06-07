#ifndef ZLEMU_CORE_SMS_TESTS_TEST_LOGGER_H
#define ZLEMU_CORE_SMS_TESTS_TEST_LOGGER_H

#include "Logger.h"

class TestLogger : public LoggerOutput
{
public:
    TestLogger()
    {
        Logger::SetOutput(this);
        Logger::SetLogLevel(LogLevel::eTrace);
        //Logger::SetTraceLevel(0xFFFFFFFF);
        Logger::SetTraceLevel(0);
    }

    void Output(std::unique_ptr<LogEntry> entry) override
    {
        (void)entry;
        //printf("%s\n", entry->message.c_str());
    }
};

#endif