#include "Aurora/Core/Logger.h"

#include <atomic>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <mutex>
#include <string>

#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif

namespace Aurora
{
    namespace
    {
        std::atomic<LogLevel> s_Level{LogLevel::Trace};
        std::mutex s_Mutex;

        const char *LevelName(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Trace:
                return "TRACE";
            case LogLevel::Debug:
                return "DEBUG";
            case LogLevel::Info:
                return "INFO ";
            case LogLevel::Warn:
                return "WARN ";
            case LogLevel::Error:
                return "ERROR";
            case LogLevel::Critical:
                return "CRIT ";
            }
            return "?????";
        }

        const char *LevelColor(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Trace:
                return "\033[90m";
            case LogLevel::Debug:
                return "\033[36m";
            case LogLevel::Info:
                return "\033[32m";
            case LogLevel::Warn:
                return "\033[33m";
            case LogLevel::Error:
                return "\033[31m";
            case LogLevel::Critical:
                return "\033[1;41m";
            }
            return "";
        }

        bool UseColor(std::FILE *stream)
        {
#if defined(__unix__) || defined(__APPLE__)
            return ::isatty(::fileno(stream)) != 0;
#else
            (void)stream;
            return false;
#endif
        }
    }

    void Logger::SetLevel(LogLevel level)
    {
        s_Level.store(level);
    }

    LogLevel Logger::GetLevel()
    {
        return s_Level.load();
    }

    void Logger::Write(LogLevel level, std::string_view message)
    {
        using namespace std::chrono;
        const auto now = system_clock::now();
        const std::time_t t = system_clock::to_time_t(now);
        const auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count() % 1000;

        std::tm tm{};
#if defined(_WIN32)
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        char timeBuf[16];
        std::strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &tm);

        std::FILE *out = (level >= LogLevel::Error) ? stderr : stdout;
        const bool color = UseColor(out);

        std::lock_guard<std::mutex> lock(s_Mutex);
        if (color)
            std::fprintf(out, "%s[%s.%03d] [%s] %.*s\033[0m\n", LevelColor(level), timeBuf, static_cast<int>(ms),
                         LevelName(level), static_cast<int>(message.size()), message.data());
        else
            std::fprintf(out, "[%s.%03d] [%s] %.*s\n", timeBuf, static_cast<int>(ms), LevelName(level),
                         static_cast<int>(message.size()), message.data());
        std::fflush(out);
    }
}
