#pragma once

#include <cstdlib>
#include <format>
#include <string_view>
#include <utility>

namespace Aurora
{
    enum class LogLevel
    {
        Trace = 0,
        Debug,
        Info,
        Warn,
        Error,
        Critical
    };

    class Logger
    {
    public:
        static void SetLevel(LogLevel level);
        static LogLevel GetLevel();

        static void Write(LogLevel level, std::string_view message);

        template <typename... Args>
        static void Log(LogLevel level, std::format_string<Args...> fmt, Args &&...args)
        {
            if (level < GetLevel())
                return;
            Write(level, std::format(fmt, std::forward<Args>(args)...));
        }
    };
}

#define AURORA_LOG_TRACE(...) ::Aurora::Logger::Log(::Aurora::LogLevel::Trace, __VA_ARGS__)
#define AURORA_LOG_INFO(...) ::Aurora::Logger::Log(::Aurora::LogLevel::Info, __VA_ARGS__)
#define AURORA_LOG_WARN(...) ::Aurora::Logger::Log(::Aurora::LogLevel::Warn, __VA_ARGS__)
#define AURORA_LOG_ERROR(...) ::Aurora::Logger::Log(::Aurora::LogLevel::Error, __VA_ARGS__)
#define AURORA_LOG_CRITICAL(...) ::Aurora::Logger::Log(::Aurora::LogLevel::Critical, __VA_ARGS__)

#ifndef AURORA_DISABLE_ASSERTS
#define AURORA_ASSERT(condition, ...)                                                              \
    do                                                                                             \
    {                                                                                              \
        if (!(condition))                                                                          \
        {                                                                                          \
            ::Aurora::Logger::Log(::Aurora::LogLevel::Critical,                                    \
                                  "Assertion failed: {} ({}:{})", #condition, __FILE__, __LINE__); \
            ::Aurora::Logger::Log(::Aurora::LogLevel::Critical, __VA_ARGS__);                      \
            std::abort();                                                                          \
        }                                                                                          \
    } while (false)
#else
#define AURORA_ASSERT(condition, ...) ((void)0)
#endif
