#pragma once

#include <cstdint>

namespace Aurora
{
    class Time
    {
        friend class Application;

    public:
        static void Init();
        static void Update();

        static float DeltaTime();

        static float GetFPS();

        static double GetElapsedTime();

        static uint64_t GetFrameCount();
    };

}