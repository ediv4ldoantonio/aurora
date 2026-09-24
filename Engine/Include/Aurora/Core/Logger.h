#pragma once

#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <cstdlib>

namespace Aurora
{
    enum class LogLevel
    {
        Trace = 0,
        Info = 1,
        Warn = 2,
        Error = 3,
        Critical = 4
    };

    class Logger
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void SetLevel(LogLevel level);

        template <typename... Args>
        static void Trace(Args &&...args)
        {
            Write(LogLevel::Trace, BuildMessage(std::forward<Args>(args)...));
        }

        template <typename... Args>
        static void Info(Args &&...args)
        {
            Write(LogLevel::Info, BuildMessage(std::forward<Args>(args)...));
        }

        template <typename... Args>
        static void Warn(Args &&...args)
        {
            Write(LogLevel::Warn, BuildMessage(std::forward<Args>(args)...));
        }

        template <typename... Args>
        static void Error(Args &&...args)
        {
            Write(LogLevel::Error, BuildMessage(std::forward<Args>(args)...));
        }

        template <typename... Args>
        static void Critical(Args &&...args)
        {
            Write(LogLevel::Critical, BuildMessage(std::forward<Args>(args)...));
        }

    private:
        static void Write(LogLevel level, const std::string &message);

        template <typename... Args>
        static std::string BuildMessage(Args &&...args)
        {
            std::ostringstream stream;
            (stream << ... << args);
            return stream.str();
        }

    private:
        static LogLevel s_Level;
        static bool s_Initialized;
    };
}

#define AURORA_LOG_TRACE(...) ::Aurora::Logger::Trace(__VA_ARGS__)
#define AURORA_LOG_INFO(...) ::Aurora::Logger::Info(__VA_ARGS__)
#define AURORA_LOG_WARN(...) ::Aurora::Logger::Warn(__VA_ARGS__)
#define AURORA_LOG_ERROR(...) ::Aurora::Logger::Error(__VA_ARGS__)
#define AURORA_LOG_CRITICAL(...) ::Aurora::Logger::Critical(__VA_ARGS__)

#ifndef AURORA_DISABLE_ASSERTS
#define AURORA_ASSERT(condition, ...)                                                            \
    do                                                                                           \
    {                                                                                            \
        if (!(condition))                                                                        \
        {                                                                                        \
            AURORA_LOG_CRITICAL("Assertion failed: {} ({}:{})", #condition, __FILE__, __LINE__); \
            AURORA_LOG_CRITICAL(__VA_ARGS__);                                                    \
            std::abort();                                                                        \
        }                                                                                        \
    } while (false)
#else
#define AURORA_ASSERT(condition, ...) ((void)0)
#endif
