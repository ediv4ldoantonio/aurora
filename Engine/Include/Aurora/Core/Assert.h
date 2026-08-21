#pragma once

#include <Aurora/Core/Logger.h>

#include <cstdlib>

#ifndef NDEBUG
#define AURORA_ASSERT(condition)                                   \
    do                                                             \
    {                                                              \
        if (!(condition))                                          \
        {                                                          \
            AURORA_LOG_CRITICAL("Assertion failed: ", #condition); \
            std::abort();                                          \
        }                                                          \
    } while (false)
#else
#define AURORA_ASSERT(condition) ((void)0)
#endif
