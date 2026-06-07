#ifndef ZLEMU_CORE_LOGGER_H
#define ZLEMU_CORE_LOGGER_H


#include <memory>
#include <stdarg.h>
#include <string>
#include <string.h>
#include <sys/time.h>


enum class LogLevel
{
    eError,
    eWarning,
    eInfo,
    eDebug,
    eTrace
};

// Trace level logs are very verbose, this allows to turn them on/off for each subsystem.
enum class TraceLogLevel : uint32_t
{
    eCpu = 0x01,
    ePpu = 0x02,
    eMemory = 0x04,
    eInput = 0x08,
    eTimer = 0x10,
    eInterrupt = 0x20,
    eApu = 0x40,
    eDma = 0x80,
};


class LogEntry
{
public:
    LogEntry(LogLevel level, const std::string &message) :
        level(level),
        message(message)
    {
        gettimeofday(&tv, nullptr);
    }

    timeval tv;
    LogLevel level;
    std::string message;
};


class LoggerOutput
{
public:
    virtual ~LoggerOutput() = default;
    virtual void Output(std::unique_ptr<LogEntry> entry) = 0;
};


class Logger
{
public:
    static void Log(LogLevel level, const char *format, ...)
    {
        if (level > logLevel || loggerOutput == nullptr)
            return;

        char buf[1024];

        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);

        loggerOutput->Output(std::make_unique<LogEntry>(level, buf));
    }

    static void TraceLog(std::string_view label, const char *format, ...)
    {
        if (loggerOutput == nullptr)
            return;

        char buf[1024];
        const size_t bytesToCopy = std::min(label.size(), sizeof(buf) - 1);
        memcpy(buf, label.data(), bytesToCopy);

        va_list args;
        va_start(args, format);
        vsnprintf(buf + bytesToCopy, sizeof(buf) - bytesToCopy, format, args);
        va_end(args);

        loggerOutput->Output(std::make_unique<LogEntry>(LogLevel::eTrace, buf));
    }

    static void SetOutput(LoggerOutput *output) {loggerOutput = output;}
    static void SetLogLevel(LogLevel level) {logLevel = level;}
    static void SetTraceLevel(uint32_t level) {traceLevel = level;}
    static LogLevel GetLogLevel() {return logLevel;}
    static uint32_t GetTraceLevel() {return traceLevel;}
    static inline bool IsTraceLevel(TraceLogLevel level)
    {
        return (logLevel == LogLevel::eTrace) &&
               (traceLevel & static_cast<uint32_t>(level)) &&
               (loggerOutput != nullptr);
    }

private:
    static LoggerOutput *loggerOutput;

    static LogLevel logLevel;
    static uint32_t traceLevel;
};

#define LogError(...)       do {Logger::Log(LogLevel::eError, __VA_ARGS__);} while (0)
#define LogWarning(...)     do {Logger::Log(LogLevel::eWarning, __VA_ARGS__);} while (0)
#define LogInfo(...)        do {Logger::Log(LogLevel::eInfo, __VA_ARGS__);} while (0)
#define LogDebug(...)       do {Logger::Log(LogLevel::eDebug, __VA_ARGS__);} while (0)
#define LogTrace(...)       do {Logger::Log(LogLevel::eTrace, __VA_ARGS__);} while (0)

// Subsystem specific trace level logs.
#define LogCpu(...)       do {if (Logger::IsTraceLevel(TraceLogLevel::eCpu))       Logger::TraceLog("Cpu:      ", __VA_ARGS__);} while (0)
#define LogPpu(...)       do {if (Logger::IsTraceLevel(TraceLogLevel::ePpu))       Logger::TraceLog("Ppu       ", __VA_ARGS__);} while (0)
#define LogMemory(...)    do {if (Logger::IsTraceLevel(TraceLogLevel::eMemory))    Logger::TraceLog("Memory:   ", __VA_ARGS__);} while (0)
#define LogInput(...)     do {if (Logger::IsTraceLevel(TraceLogLevel::eInput))     Logger::TraceLog("Input:    ", __VA_ARGS__);} while (0)
#define LogTimer(...)     do {if (Logger::IsTraceLevel(TraceLogLevel::eTimer))     Logger::TraceLog("Timer:    ", __VA_ARGS__);} while (0)
#define LogInterrupt(...) do {if (Logger::IsTraceLevel(TraceLogLevel::eInterrupt)) Logger::TraceLog("Int:      ", __VA_ARGS__);} while (0)
#define LogApu(...)       do {if (Logger::IsTraceLevel(TraceLogLevel::eApu))       Logger::TraceLog("Apu:      ", __VA_ARGS__);} while (0)


#endif
